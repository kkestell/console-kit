namespace ConsoleKit;

public enum KeyCode
{
    Unknown,

    // Letter keys
    A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

    // Number keys
    Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,

    // Symbol keys
    Minus, Equals, Semicolon, Apostrophe, Comma, Period, Slash, Backslash,
    Backtick, OpenBracket, CloseBracket,

    // Arrow keys
    Up, Down, Right, Left,

    // Function keys
    F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,

    // Special keys
    Escape, Tab, CapsLock, Enter, Space, Backspace, Delete, Insert, Home, End,
    PageUp, PageDown, ControlLeft, ControlRight, ShiftLeft, ShiftRight, AltLeft, AltRight,
    SuperLeft, SuperRight,

    // Numpad keys (Num Lock OFF)
    NumpadIns, NumpadEnd, NumpadDown, NumpadPgDn, NumpadLeft, NumpadCenter,
    NumpadRight, NumpadHome, NumpadUp, NumpadPgUp, NumpadDel,

    // Numpad keys (Num Lock ON)
    Numpad0, Numpad1, Numpad2, Numpad3, Numpad4, Numpad5, Numpad6,
    Numpad7, Numpad8, Numpad9, NumpadDot,

    // Numpad operation keys
    NumpadDivide, NumpadMultiply, NumpadMinus, NumpadPlus, NumpadEnter, NumLock,
}

public static class KeyCodeExtensions
{
    private static readonly Dictionary<string, KeyCode> KeyCodes = new(StringComparer.OrdinalIgnoreCase)
    {
        // Letter keys
        { "97u",     KeyCode.A },
        { "98u",     KeyCode.B },
        { "99u",     KeyCode.C },
        { "100u",    KeyCode.D },
        { "101u",    KeyCode.E },
        { "102u",    KeyCode.F },
        { "103u",    KeyCode.G },
        { "104u",    KeyCode.H },
        { "105u",    KeyCode.I },
        { "106u",    KeyCode.J },
        { "107u",    KeyCode.K },
        { "108u",    KeyCode.L },
        { "109u",    KeyCode.M },
        { "110u",    KeyCode.N },
        { "111u",    KeyCode.O },
        { "112u",    KeyCode.P },
        { "113u",    KeyCode.Q },
        { "114u",    KeyCode.R },
        { "115u",    KeyCode.S },
        { "116u",    KeyCode.T },
        { "117u",    KeyCode.U },
        { "118u",    KeyCode.V },
        { "119u",    KeyCode.W },
        { "120u",    KeyCode.X },
        { "121u",    KeyCode.Y },
        { "122u",    KeyCode.Z },

        // Number keys
        { "48u",     KeyCode.Num0 },
        { "49u",     KeyCode.Num1 },
        { "50u",     KeyCode.Num2 },
        { "51u",     KeyCode.Num3 },
        { "52u",     KeyCode.Num4 },
        { "53u",     KeyCode.Num5 },
        { "54u",     KeyCode.Num6 },
        { "55u",     KeyCode.Num7 },
        { "56u",     KeyCode.Num8 },
        { "57u",     KeyCode.Num9 },

        // Symbol keys
        { "45u",     KeyCode.Minus },
        { "61u",     KeyCode.Equals },
        { "59u",     KeyCode.Semicolon },
        { "39u",     KeyCode.Apostrophe },
        { "44u",     KeyCode.Comma },
        { "46u",     KeyCode.Period },
        { "47u",     KeyCode.Slash },
        { "92u",     KeyCode.Backslash },
        { "96u",     KeyCode.Backtick },
        { "91u",     KeyCode.OpenBracket },
        { "93u",     KeyCode.CloseBracket },

        // Arrow keys
        { "1A",      KeyCode.Up },
        { "1B",      KeyCode.Down },
        { "1C",      KeyCode.Right },
        { "1D",      KeyCode.Left },

        // Function keys
        { "1P",      KeyCode.F1 },
        { "1Q",      KeyCode.F2 },
        { "13~",     KeyCode.F3 },
        { "1S",      KeyCode.F4 },
        { "15~",     KeyCode.F5 },
        { "17~",     KeyCode.F6 },
        { "18~",     KeyCode.F7 },
        { "19~",     KeyCode.F8 },
        { "20~",     KeyCode.F9 },
        { "21~",     KeyCode.F10 },
        { "23~",     KeyCode.F11 },
        { "24~",     KeyCode.F12 },

        // Special keys
        { "27u",     KeyCode.Escape },
        { "9u",      KeyCode.Tab },
        { "57358u",  KeyCode.CapsLock },
        { "13u",     KeyCode.Enter },
        { "32u",     KeyCode.Space },
        { "8u",      KeyCode.Backspace },
        { "3~",      KeyCode.Delete },
        { "2~",      KeyCode.Insert },
        { "1H",      KeyCode.Home },
        { "1F",      KeyCode.End },
        { "5~",      KeyCode.PageUp },
        { "6~",      KeyCode.PageDown },
        { "57442u",  KeyCode.ControlLeft },
        { "57448u", KeyCode.ControlRight },
        { "57441u",  KeyCode.ShiftLeft },
        { "57447u", KeyCode.ShiftRight },
        { "57443u",  KeyCode.AltLeft },
        { "57449u", KeyCode.AltRight },
        { "57444u", KeyCode.SuperLeft },
        { "57450u", KeyCode.SuperRight },

        // Numpad keys (Num Lock OFF)
        { "57425u",  KeyCode.NumpadIns },
        { "57424u",  KeyCode.NumpadEnd },
        { "57420u",  KeyCode.NumpadDown },
        { "57422u",  KeyCode.NumpadPgDn },
        { "57417u",  KeyCode.NumpadLeft },
        { "57427u",  KeyCode.NumpadCenter },
        { "57418u",  KeyCode.NumpadRight },
        { "57423u",  KeyCode.NumpadHome },
        { "57419u",  KeyCode.NumpadUp },
        { "57421u",  KeyCode.NumpadPgUp },
        { "57426u",  KeyCode.NumpadDel },

        // Numpad keys (Num Lock ON)
        { "57399u",  KeyCode.Numpad0 },
        { "57400u",  KeyCode.Numpad1 },
        { "57401u",  KeyCode.Numpad2 },
        { "57402u",  KeyCode.Numpad3 },
        { "57403u",  KeyCode.Numpad4 },
        { "57404u",  KeyCode.Numpad5 },
        { "57405u",  KeyCode.Numpad6 },
        { "57406u",  KeyCode.Numpad7 },
        { "57407u",  KeyCode.Numpad8 },
        { "57408u",  KeyCode.Numpad9 },
        { "57409u",  KeyCode.NumpadDot },

        // Numpad operation keys
        { "57410u",  KeyCode.NumpadDivide },
        { "57411u",  KeyCode.NumpadMultiply },
        { "57412u",  KeyCode.NumpadMinus },
        { "57413u",  KeyCode.NumpadPlus },
        { "57414u",  KeyCode.NumpadEnter },
        { "57360u",  KeyCode.NumLock }
    };

    public static KeyCode FromCode(string keyCode)
    {
        KeyCodes.TryGetValue(keyCode, out var code);
        
        if (code == KeyCode.Unknown)
            Console.WriteLine("Unknown key code: {0}", keyCode);
        
        return code;
    }

    public static string ToDisplayString(this KeyCode keyCode) => keyCode.ToString();
}