namespace ConsoleKit;


public enum MouseEventType
{
    Press,
    Release,
    Motion,
    WheelUp,
    WheelDown,
    Unknown
}

public enum MouseButton
{
    Left,
    Middle,
    Right,
    Other,
    None
}

public abstract record Event();

public record KeyboardEvent(KeyCode Key, Modifier Modifiers) : Event;

public record MouseEvent(MouseEventType Type, MouseButton Button, int X, int Y, Modifier Modifiers) : Event;