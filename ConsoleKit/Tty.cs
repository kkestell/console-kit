using System.Diagnostics;

namespace ConsoleKit;

public class Tty : IDisposable
{
    private static Tty? _instance;
    private bool _isDisposed;
    private readonly string _originalTtySettings;
    
    private Tty()
    {
        _originalTtySettings = ExecuteCommand("stty -g");
    }

    private static Tty Instance => _instance ??= new Tty();
    
    public static Tty Begin()
    {
        return Instance;
    }
    
    public void EnableRawMode()
    {
        ExecuteCommand("stty raw -echo");
    }
    
    public void DisableEcho()
    {
        ExecuteCommand("stty -echo");
    }
    
    private static string ExecuteCommand(string command)
    {
        var processInfo = new ProcessStartInfo
        {
            FileName = "/bin/bash",
            Arguments = $"-c \"{command}\"",
            RedirectStandardOutput = true,
            RedirectStandardError = true,
            UseShellExecute = false,
            CreateNoWindow = true
        };
        
        using var process = Process.Start(processInfo);
        var output = process?.StandardOutput.ReadToEnd() ?? string.Empty;
        process?.WaitForExit();
        
        return output.Trim();
    }
    
    public void Dispose()
    {
        Dispose(true);
        GC.SuppressFinalize(this);
    }
    
    protected virtual void Dispose(bool disposing)
    {
        if (_isDisposed)
            return;
            
        if (disposing && !string.IsNullOrEmpty(_originalTtySettings))
        {
            ExecuteCommand($"stty {_originalTtySettings}");
            Console.CursorVisible = true;
        }
        
        _isDisposed = true;
        _instance = null;
    }
    
    ~Tty()
    {
        Dispose(false);
    }
}