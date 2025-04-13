#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "keyboard.h"
#include "event.h"

void enable_keyboard()
{
    printf("\033[>8u");
    fflush(stdout);
}

void disable_keyboard()
{
    printf("\033[<u");
    fflush(stdout);
}

bool is_keyboard_event(const unsigned char* bytes, int length)
{
    return length >= 2 && bytes[0] == 0x1B && bytes[1] == 0x5B;
}

static void print_bytes_hex(const unsigned char* bytes, int length)
{
    for (int i = 0; i < length; i++) {
        if (i == 0) {
            printf("ESC");
        } else {
            printf("%c", bytes[i]);
        }
    }
    printf("\n");
    fflush(stdout);
}

KeyEventData parse_keyboard_event(const unsigned char* bytes, int length)
{
    KeyEventData event = {
        .event_type = KEY_EVENT_PRESS,
        .key_code = KEY_UNKNOWN,
        .modifiers = MODIFIER_NONE,
        .utf8 = {0}
    };

    // Print the raw bytes in octal for debugging
    print_bytes_hex(bytes, length);

    // For now, just return a dummy KEY_UNKNOWN event
    return event;
}