using System;
using System.Runtime.InteropServices;

namespace ConsoleKit;

public static class Termios
{
    // Standard file descriptors
    public const int StdinFileno = 0;
    public const int StdoutFileno = 1;
    public const int StderrFileno = 2;
    
    // tcsetattr actions
    public const int TcsaNow = 0;
    public const int TcsaDrain = 1;
    public const int TcsaFlush = 2;
    
    // Poll flag
    public const short PollIn = 0x0001;
    
    // Index for c_cc array
    public const int VMin = 6;
    public const int VTime = 5;
    
    // c_iflag bits
    public const uint IgnBrk = 0x00000001;
    public const uint BrkInt = 0x00000002;
    public const uint IgnPar = 0x00000004;
    public const uint ParMrk = 0x00000008;
    public const uint InPck = 0x00000010;
    public const uint IStrip = 0x00000020;
    public const uint InLcr = 0x00000040;
    public const uint IgnCr = 0x00000080;
    
    // c_oflag bits
    public const uint OPost = 0x00000001;
    
    // c_cflag bits
    public const uint CS8 = 0x00000008;
    
    // c_lflag bits
    public const uint Echo = 0x00000001;
    public const uint EchoNl = 0x00000002;
    public const uint ICanon = 0x00000004;
    public const uint ISig = 0x00000008;
    
    [StructLayout(LayoutKind.Sequential)]
    public struct TermiosStruct
    {
        // Internal fields to match C structure
        private uint c_iflag;    
        private uint c_oflag;    
        private uint c_cflag;    
        private uint c_lflag;    
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
        private byte[] c_cc;     
        private uint c_ispeed;   
        private uint c_ospeed;
        
        // Public properties with .NET naming conventions
        public uint InputFlags 
        { 
            get => c_iflag; 
            set => c_iflag = value; 
        }
        
        public uint OutputFlags 
        { 
            get => c_oflag; 
            set => c_oflag = value; 
        }
        
        public uint ControlFlags 
        { 
            get => c_cflag; 
            set => c_cflag = value; 
        }
        
        public uint LocalFlags 
        { 
            get => c_lflag; 
            set => c_lflag = value; 
        }
        
        public byte[] ControlChars 
        { 
            get => c_cc; 
            set => c_cc = value; 
        }
        
        public uint InputSpeed 
        { 
            get => c_ispeed; 
            set => c_ispeed = value; 
        }
        
        public uint OutputSpeed 
        { 
            get => c_ospeed; 
            set => c_ospeed = value; 
        }
    }
    
    [StructLayout(LayoutKind.Sequential)]
    public struct Pollfd
    {
        // Keep field names for P/Invoke compatibility but add properties
        private int fd;
        private short events;
        private short revents;
        
        public int FileDescriptor 
        { 
            get => fd; 
            set => fd = value; 
        }
        
        public short Events 
        { 
            get => events; 
            set => events = value; 
        }
        
        public short ReturnedEvents 
        { 
            get => revents; 
            set => revents = value; 
        }
    }
    
    [DllImport("libc", EntryPoint = "tcgetattr")]
    public static extern int TcGetAttr(int fd, out TermiosStruct termios);
    
    [DllImport("libc", EntryPoint = "tcsetattr")]
    public static extern int TcSetAttr(int fd, int optional_actions, ref TermiosStruct termios);
    
    [DllImport("libc", EntryPoint = "poll")]
    public static extern int Poll(ref Pollfd fds, uint nfds, int timeout);
    
    [DllImport("libc", EntryPoint = "read")]
    public static extern int Read(int fd, byte[] buf, int count);
    
    [DllImport("libc", EntryPoint = "write")]
    public static extern int Write(int fd, byte[] buf, int count);
    
    // Helper method to set terminal to raw mode
    public static TermiosStruct SetRawMode(int fd)
    {
        if (TcGetAttr(fd, out var original) != 0)
            throw new InvalidOperationException("Failed to get terminal attributes");
            
        var raw = original;
        
        // Input flags - disable break processing
        raw.InputFlags &= ~(IgnBrk | BrkInt | ParMrk | IStrip | InLcr | IgnCr | InPck);
        
        // Output flags - disable post processing
        raw.OutputFlags &= ~OPost;
        
        // Control flags - set 8 bit chars
        raw.ControlFlags |= CS8;
        
        // Local flags - disable echo, canonical mode, signals
        raw.LocalFlags &= ~(Echo | EchoNl | ICanon | ISig);
        
        // Control chars - set return conditions: min number of bytes and timer
        raw.ControlChars[VMin] = 1;    // Return when 1 char is available
        raw.ControlChars[VTime] = 0;   // No timeout
        
        // Apply settings
        if (TcSetAttr(fd, TcsaNow, ref raw) != 0)
            throw new InvalidOperationException("Failed to set terminal attributes");
            
        return original;
    }
}