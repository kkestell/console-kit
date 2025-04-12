using System.Text;
using System.Text.RegularExpressions;

namespace ConsoleKit;

public static class Keyboard
{
    private static readonly Regex Form1Regex = new(@"(\d+)(?:;(\d+))?([u~])", RegexOptions.Compiled);
    private static readonly Regex Form2Regex = new(@"(?:1;(\d+))?([ABCDEFHPQS])", RegexOptions.Compiled);

    public static void Enable()
    {
        Console.Write("\e[>8u");
        Console.Out.Flush();
    }
    
    public static void Disable()
    {
        Console.Write("\e[<u");
        Console.Out.Flush();
    }
    
    public static bool IsKeyboardEvent(ReadOnlySpan<byte> bytes)
    {
        return bytes.Length >= 2 && bytes[0] == 0x1b && bytes[1] == 0x5b;
    }

    public static KeyboardEvent ParseEvent(ReadOnlySpan<byte> bytes)
    {
        if (bytes.Length < 2 || bytes[0] != 0x1b || bytes[1] != 0x5b)
            throw new FormatException($"Invalid Kitty keyboard event: {BitConverter.ToString(bytes.ToArray())}");
        
        var content = Encoding.UTF8.GetString(bytes[2..]);
        
        // Form 1: number ; modifiers [u~]
        var match = Form1Regex.Match(content);
        if (match.Success)
        {
            var number = match.Groups[1].Value;
            var modifiers = match.Groups[2].Value;
            var suffix = match.Groups[3].Value;
            
            var keyCode = $"{number}{suffix}";
            var keyEnum = KeyCodeExtensions.FromCode(keyCode);
            var mods = DecodeModifiers(modifiers);
            
            return new KeyboardEvent(keyEnum, mods);
        }
        
        // Form 2: 1; modifiers [ABCDEFHPQS]
        match = Form2Regex.Match(content);
        if (match.Success)
        {
            var modifiers = match.Groups[1].Value;
            var suffix = match.Groups[2].Value;
            
            var keyCode = $"1{suffix}";
            var keyEnum = KeyCodeExtensions.FromCode(keyCode);
            var mods = DecodeModifiers(modifiers);
            
            return new KeyboardEvent(keyEnum, mods);
        }
        
        throw new FormatException("Invalid Kitty code: does not match expected format");
    }
    
    private static Modifier DecodeModifiers(string? modValue)
    {
        if (string.IsNullOrEmpty(modValue) || modValue == "None" || int.Parse(modValue) <= 1)
            return Modifier.None;
        
        var modBits = int.Parse(modValue) - 1;
        var result = Modifier.None;
        
        for (var i = 0; i < 8; i++)
            if ((modBits & (1 << i)) != 0)
                result |= (Modifier)(1 << i);
        
        return result;
    }
}