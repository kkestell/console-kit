#pragma once

#include <stdbool.h>

// Modifier flags
typedef enum {
    MODIFIER_NONE = 0,
    MODIFIER_SHIFT = 1 << 0,
    MODIFIER_ALT = 1 << 1,
    MODIFIER_CTRL = 1 << 2,
    MODIFIER_SUPER = 1 << 3,
    MODIFIER_HYPER = 1 << 4,
    MODIFIER_META = 1 << 5,
    MODIFIER_CAPSLOCK = 1 << 6,
    MODIFIER_NUMLOCK = 1 << 7
} Modifier;

// Mouse event types
typedef enum {
    MOUSE_EVENT_PRESS,
    MOUSE_EVENT_RELEASE,
    MOUSE_EVENT_MOTION,
    MOUSE_EVENT_WHEEL_UP,
    MOUSE_EVENT_WHEEL_DOWN,
    MOUSE_EVENT_UNKNOWN
} MouseEventType;

// Mouse buttons
typedef enum {
    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_MIDDLE,
    MOUSE_BUTTON_RIGHT,
    MOUSE_BUTTON_OTHER,
    MOUSE_BUTTON_NONE
} MouseButton;

// Key codes
typedef enum {
    KEY_UNKNOWN,

    // Letter keys
    KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M,
    KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z,

    // Number keys
    KEY_NUM0, KEY_NUM1, KEY_NUM2, KEY_NUM3, KEY_NUM4, KEY_NUM5, KEY_NUM6, KEY_NUM7, KEY_NUM8, KEY_NUM9,

    // Symbol keys
    KEY_MINUS, KEY_EQUALS, KEY_SEMICOLON, KEY_APOSTROPHE, KEY_COMMA, KEY_PERIOD, KEY_SLASH, KEY_BACKSLASH,
    KEY_BACKTICK, KEY_OPEN_BRACKET, KEY_CLOSE_BRACKET,

    // Arrow keys
    KEY_UP, KEY_DOWN, KEY_RIGHT, KEY_LEFT,

    // Function keys
    KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12,

    // Special keys
    KEY_ESCAPE, KEY_TAB, KEY_CAPS_LOCK, KEY_ENTER, KEY_SPACE, KEY_BACKSPACE, KEY_DELETE, KEY_INSERT, KEY_HOME, KEY_END,
    KEY_PAGE_UP, KEY_PAGE_DOWN, KEY_CTRL_LEFT, KEY_CTRL_RIGHT, KEY_SHIFT_LEFT, KEY_SHIFT_RIGHT, KEY_ALT_LEFT, KEY_ALT_RIGHT,
    KEY_SUPER_LEFT, KEY_SUPER_RIGHT,

    // Numpad keys (Num Lock OFF)
    KEY_NUMPAD_INS, KEY_NUMPAD_END, KEY_NUMPAD_DOWN, KEY_NUMPAD_PG_DN, KEY_NUMPAD_LEFT, KEY_NUMPAD_CENTER,
    KEY_NUMPAD_RIGHT, KEY_NUMPAD_HOME, KEY_NUMPAD_UP, KEY_NUMPAD_PG_UP, KEY_NUMPAD_DEL,

    // Numpad keys (Num Lock ON)
    KEY_NUMPAD_0, KEY_NUMPAD_1, KEY_NUMPAD_2, KEY_NUMPAD_3, KEY_NUMPAD_4, KEY_NUMPAD_5, KEY_NUMPAD_6,
    KEY_NUMPAD_7, KEY_NUMPAD_8, KEY_NUMPAD_9, KEY_NUMPAD_DOT,

    // Numpad operation keys
    KEY_NUMPAD_DIVIDE, KEY_NUMPAD_MULTIPLY, KEY_NUMPAD_MINUS, KEY_NUMPAD_PLUS, KEY_NUMPAD_ENTER, KEY_NUM_LOCK
} KeyCode;

// Event types
typedef enum {
    EVENT_TYPE_MOUSE,
    EVENT_TYPE_KEY,
    EVENT_TYPE_UNKNOWN
} EventType;

// Key event types
typedef enum {
    KEY_EVENT_PRESS,
    KEY_EVENT_RELEASE,
    KEY_EVENT_REPEAT
} KeyEventType;

// Mouse event structure
typedef struct {
    MouseEventType event_type;
    MouseButton button;
    int x;
    int y;
    Modifier modifiers;
} MouseEventData;

// Key event structure
typedef struct {
    KeyEventType event_type;
    KeyCode key_code;
    Modifier modifiers;
    char utf8[8]; // UTF-8 representation if available
} KeyEventData;

// Generic event structure
typedef struct {
    EventType type;
    union {
        MouseEventData mouse;
        KeyEventData key;
    } data;
} Event;

// Function to convert key code string to KeyCode enum
KeyCode key_code_from_string(const char* key_str);

// Function to get display string for key code
const char* key_code_to_string(KeyCode key_code);
