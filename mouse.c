#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "mouse.h"
#include "event.h"

void enable_mouse()
{
    printf("\033[?1006h\033[?1003h");
    fflush(stdout);
}

void disable_mouse()
{
    printf("\033[?1003l");
    fflush(stdout);
}

bool is_mouse_event(const unsigned char* bytes, int length)
{
    return length > 3 && bytes[0] == 0x1B && bytes[1] == 0x5B && bytes[2] == 0x3C;
}

// Helper function to extract integer values from ASCII string
static int parse_int(const unsigned char* start, int length, int* consumed)
{
    char buffer[16] = {0}; // Buffer to store the number
    int i = 0;
    
    // Copy digits to buffer
    while (i < length && i < 15 && isdigit(start[i])) {
        buffer[i] = start[i];
        i++;
    }
    
    // Update consumed count
    *consumed = i;
    
    // Parse and return the integer
    return atoi(buffer);
}

MouseEventData parse_mouse_event(const unsigned char* bytes, int length)
{
    MouseEventData event = {
        .event_type = MOUSE_EVENT_UNKNOWN,
        .button = MOUSE_BUTTON_NONE,
        .x = 0,
        .y = 0,
        .modifiers = MODIFIER_NONE
    };

    if (!is_mouse_event(bytes, length))
        return event;

    // Skip the "\033[<" prefix (3 bytes)
    const unsigned char* input = bytes + 3;
    int remaining = length - 3;
    int consumed = 0;

    // Parse the button code
    int button_code = parse_int(input, remaining, &consumed);
    input += consumed;
    remaining -= consumed;

    // Check for the ';' separator
    if (remaining <= 0 || *input != ';')
        return event;
    
    // Skip the separator
    input++;
    remaining--;

    // Parse x coordinate
    int x = parse_int(input, remaining, &consumed);
    input += consumed;
    remaining -= consumed;

    // Check for the ';' separator
    if (remaining <= 0 || *input != ';')
        return event;
    
    // Skip the separator
    input++;
    remaining--;

    // Parse y coordinate
    int y = parse_int(input, remaining, &consumed);
    input += consumed;
    remaining -= consumed;

    // Check for event terminator ('M' for press, 'm' for release)
    if (remaining <= 0 || (*input != 'M' && *input != 'm'))
        return event;

    bool is_press = (*input == 'M');
    int button = button_code & 3;
    bool is_motion = (button_code & 32) != 0;
    bool is_wheel = (button_code & 64) != 0;

    // Set event type and button
    if (is_wheel) {
        event.event_type = button == 0 ? MOUSE_EVENT_WHEEL_UP : MOUSE_EVENT_WHEEL_DOWN;
        event.button = MOUSE_BUTTON_NONE;
    } else if (is_motion) {
        event.event_type = MOUSE_EVENT_MOTION;
        event.button = (button_code & 3) == 3 ? MOUSE_BUTTON_NONE : 
                       button == 0 ? MOUSE_BUTTON_LEFT :
                       button == 1 ? MOUSE_BUTTON_MIDDLE :
                       button == 2 ? MOUSE_BUTTON_RIGHT : MOUSE_BUTTON_OTHER;
    } else {
        event.event_type = is_press ? MOUSE_EVENT_PRESS : MOUSE_EVENT_RELEASE;
        event.button = button == 0 ? MOUSE_BUTTON_LEFT :
                      button == 1 ? MOUSE_BUTTON_MIDDLE :
                      button == 2 ? MOUSE_BUTTON_RIGHT : MOUSE_BUTTON_OTHER;
    }

    // Set coordinates
    event.x = x;
    event.y = y;

    // Set modifiers
    if (button_code & 4) event.modifiers |= MODIFIER_SHIFT;
    if (button_code & 8) event.modifiers |= MODIFIER_ALT;
    if (button_code & 16) event.modifiers |= MODIFIER_CTRL;

    return event;
}