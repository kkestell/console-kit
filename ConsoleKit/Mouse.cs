using System.Text;

namespace ConsoleKit;

public static class Mouse
{
    public static void Enable()
    {
        Console.Write("\e[?1006h\e[?1003h");
    }
    
    public static void Disable()
    {
        Console.Write("\e[?1003l");
    }
    
    public static bool IsMouseEvent(ReadOnlySpan<byte> bytes)
    {
        return bytes.Length > 3 && bytes[0] == 0x1B && bytes[1] == 0x5B && bytes[2] == 0x3C;
    }
    
    public static MouseEvent ParseEvent(ReadOnlySpan<byte> bytes)
    {
        if (!IsMouseEvent(bytes))
            throw new FormatException($"Invalid SGR mouse event: {BitConverter.ToString(bytes.ToArray())}");

        var input = Encoding.ASCII.GetString(bytes.ToArray(), 3, bytes.Length - 3);
        var parts = input.Split([';', 'M', 'm'], StringSplitOptions.RemoveEmptyEntries);

        if (parts.Length < 3 || !int.TryParse(parts[0], out var buttonCode) || !int.TryParse(parts[1], out var x) || !int.TryParse(parts[2], out var y))
            return new MouseEvent(MouseEventType.Unknown, MouseButton.None, 0, 0, Modifier.None);

        var isPress = !input.EndsWith('m');
        var button = buttonCode & 3;
        var isMotion = (buttonCode & 32) != 0;
        var isWheel = (buttonCode & 64) != 0;

        MouseEventType eventType;
        MouseButton buttonType;

        if (isWheel)
        {
            eventType = button == 0 ? MouseEventType.WheelUp : MouseEventType.WheelDown;
            buttonType = MouseButton.None;
        }
        else if (isMotion)
        {
            eventType = MouseEventType.Motion;
            buttonType = (buttonCode & 3) == 3 ? MouseButton.None : button switch
            {
                0 => MouseButton.Left,
                1 => MouseButton.Middle,
                2 => MouseButton.Right,
                _ => MouseButton.Other
            };
        }
        else
        {
            eventType = isPress ? MouseEventType.Press : MouseEventType.Release;
            buttonType = button switch
            {
                0 => MouseButton.Left,
                1 => MouseButton.Middle,
                2 => MouseButton.Right,
                _ => MouseButton.Other
            };
        }

        var modifiers = Modifier.None;
        if ((buttonCode & 4) != 0) modifiers |= Modifier.Shift;
        if ((buttonCode & 8) != 0) modifiers |= Modifier.Alt;
        if ((buttonCode & 16) != 0) modifiers |= Modifier.Ctrl;

        return new MouseEvent(eventType, buttonType, x, y, modifiers);
    }
}