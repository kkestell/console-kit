#include <ctype.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>

#include "event.h"
#include "keyboard.h"
#include "mouse.h"

void set_raw_mode()
{
    struct termios term;

    // Get the current terminal settings
    if (tcgetattr(STDIN_FILENO, &term) == -1)
    {
        perror("tcgetattr");
        exit(1);
    }

    // Modify the terminal settings to enable raw mode
    term.c_lflag &= ~(ECHO | ICANON); // Disable echo and canonical mode
    term.c_cc[VMIN] = 1;              // Minimum number of characters to read
    term.c_cc[VTIME] = 0;             // Timeout for reads (0 means no timeout)

    // Set the modified terminal settings
    if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
    {
        perror("tcsetattr");
        exit(1);
    }
}

void reset_terminal_mode()
{
    struct termios term;

    // Get the current terminal settings
    if (tcgetattr(STDIN_FILENO, &term) == -1)
    {
        perror("tcgetattr");
        exit(1);
    }

    // Reset the terminal settings to default
    term.c_lflag |= (ECHO | ICANON); // Enable echo and canonical mode
    if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
    {
        perror("tcsetattr");
        exit(1);
    }
}

void cleanup()
{
    disable_keyboard();
    disable_mouse();
    reset_terminal_mode();
    fflush(stdout);
}

// Signal handler for Ctrl+C
void handle_signal(int sig)
{
    exit(0); // This will trigger the atexit handler
}

int main()
{
    // Set up signal handler for Ctrl+C
    signal(SIGINT, handle_signal);

    // Register normal exit handler
    atexit(cleanup);

    set_raw_mode();
    enable_keyboard();
    enable_mouse();

    // Set up fd_set for select() to monitor stdin (file descriptor 0)
    fd_set read_fds;
    struct timeval timeout;

    // Buffer for reading input
    unsigned char buffer[256];
    int bytes_read;

    while (1)
    {
        // Clear the set of file descriptors
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds); // Monitor stdin for input

        // Set the timeout to 0, resulting in a poll rather than blocking
        timeout.tv_sec = 0;
        timeout.tv_usec = 1000; // 1ms timeout for less CPU usage

        // Use select to check if there's data available on stdin
        int ret = select(STDIN_FILENO + 1, &read_fds, NULL, NULL, &timeout);
        if (ret == -1)
        {
            perror("select");
            break;
        }

        if (FD_ISSET(STDIN_FILENO, &read_fds))
        {
            // Read a chunk of data
            bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer));

            if (bytes_read > 0)
            {
                // Check if it's a mouse event
                if (is_mouse_event(buffer, bytes_read))
                {
                    MouseEventData mouse_event = parse_mouse_event(buffer, bytes_read);

                    // Print raw event data
                    printf("MOUSE: type=%d button=%d x=%d y=%d mods=%d\n", mouse_event.event_type, mouse_event.button,
                           mouse_event.x, mouse_event.y, mouse_event.modifiers);

                    // Flush output to ensure it's displayed immediately
                    fflush(stdout);
                }
                else if (is_keyboard_event(buffer, bytes_read))
                {
                    KeyEventData keyboard_event = parse_keyboard_event(buffer, bytes_read);
                }
            }
        }
    }

    return 0;
}