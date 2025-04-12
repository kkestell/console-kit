namespace ConsoleKit;

[Flags]
public enum Modifier
{
    None = 0,
    Shift = 1 << 0,
    Alt = 1 << 1,
    Ctrl = 1 << 2,
    Super = 1 << 3,
    Hyper = 1 << 4,
    Meta = 1 << 5,
    CapsLock = 1 << 6,
    NumLock = 1 << 7
}

public static class ModifierExtensions
{
    public static string ToModifierString(this Modifier modifier)
    {
        if (modifier == Modifier.None)
            return "None";

        var parts = new List<string>();
        foreach (var flag in Enum.GetValues<Modifier>())
        {
            if (flag != Modifier.None && modifier.HasFlag(flag))
                parts.Add(flag.ToString());
        }

        return string.Join(", ", parts);
    }
}