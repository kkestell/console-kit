namespace ConsoleKit.Demo;

public class Program
{
    public static void Main()
    {
        if (!OperatingSystem.IsLinux() && !OperatingSystem.IsMacOS())
            throw new PlatformNotSupportedException("This program is only supported on Linux and macOS.");

        Termios.TermiosStruct originalTermios = default;

        try
        {
            originalTermios = Termios.SetRawMode(Termios.StdinFileno);

            Mouse.Enable();
            Keyboard.Enable();

            var pollFd = new Termios.Pollfd
            {
                FileDescriptor = Termios.StdinFileno,
                Events = Termios.PollIn
            };

            var buffer = new byte[32];
            var bytesRead = new List<byte>();

            while (true)
            {
                if (Termios.Poll(ref pollFd, 1, -1) <= 0) 
                    continue;
                
                bytesRead.Clear();

                while (true)
                {
                    if (Termios.Poll(ref pollFd, 1, 0) <= 0)
                        break;

                    var count = Termios.Read(Termios.StdinFileno, buffer, buffer.Length);
                    if (count <= 0)
                        break;

                    bytesRead.AddRange(buffer.AsSpan(0, count).ToArray());
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
            }
        }
        finally
        {
            Keyboard.Disable();
            Mouse.Disable();

            if (originalTermios.ControlChars != null)
                Termios.TcSetAttr(Termios.StdinFileno, Termios.TcsaNow, ref originalTermios);
        }
    }
}
