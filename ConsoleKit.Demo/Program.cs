namespace ConsoleKit.Demo;

public class Program
{
    public static void Main()
    {
        using var tty = Tty.Begin();

        try
        {
            tty.EnableRawMode();
            tty.DisableEcho();

            Mouse.Enable();
            Keyboard.Enable();

            var bytesRead = new List<byte>();

            while (true)
            {
                var ch = Console.ReadKey(intercept: true).KeyChar;
                bytesRead.Add((byte)ch);
                
                while (Console.KeyAvailable)
                {
                    ch = Console.ReadKey(intercept: true).KeyChar;
                    bytesRead.Add((byte)ch);
                }

                if (bytesRead.Count <= 0) 
                    continue;
                    
                var data = bytesRead.ToArray();

                if (Mouse.IsMouseEvent(data))
                {
                    var mouseEvent = Mouse.ParseEvent(data);
                    Console.WriteLine($"{mouseEvent}\r");
                }
                else if (Keyboard.IsKeyboardEvent(data))
                {
                    var keyboardEvent = Keyboard.ParseEvent(data);
                    Console.WriteLine($"{keyboardEvent}\r");
                    
                    if (keyboardEvent.Key == KeyCode.Escape)
                        break;
                }
                else
                {
                    throw new Exception($"Don't know what to do with {BitConverter.ToString(data)}");
                }

                Console.Out.Flush();
                bytesRead.Clear();
            }
        }
        finally
        {
            Keyboard.Disable();
            Mouse.Disable();
        }
    }
}