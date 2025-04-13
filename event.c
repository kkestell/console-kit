#include <stdio.h>
#include <string.h>
#include "event.h"

// Key code mapping table
typedef struct {
    const char* code;
    KeyCode key;
} KeyCodeMapping;

// Key code mappings
static const KeyCodeMapping KEY_CODE_MAPPINGS[] = {
    // Letter keys
    { "97u",     KEY_A },
    { "98u",     KEY_B },
    { "99u",     KEY_C },
    { "100u",    KEY_D },
    { "101u",    KEY_E },
    { "102u",    KEY_F },
    { "103u",    KEY_G },
    { "104u",    KEY_H },
    { "105u",    KEY_I },
    { "106u",    KEY_J },
    { "107u",    KEY_K },
    { "108u",    KEY_L },
    { "109u",    KEY_M },
    { "110u",    KEY_N },
    { "111u",    KEY_O },
    { "112u",    KEY_P },
    { "113u",    KEY_Q },
    { "114u",    KEY_R },
    { "115u",    KEY_S },
    { "116u",    KEY_T },
    { "117u",    KEY_U },
    { "118u",    KEY_V },
    { "119u",    KEY_W },
    { "120u",    KEY_X },
    { "121u",    KEY_Y },
    { "122u",    KEY_Z },

    // Number keys
    { "48u",     KEY_NUM0 },
    { "49u",     KEY_NUM1 },
    { "50u",     KEY_NUM2 },
    { "51u",     KEY_NUM3 },
    { "52u",     KEY_NUM4 },
    { "53u",     KEY_NUM5 },
    { "54u",     KEY_NUM6 },
    { "55u",     KEY_NUM7 },
    { "56u",     KEY_NUM8 },
    { "57u",     KEY_NUM9 },

    // Symbol keys
    { "45u",     KEY_MINUS },
    { "61u",     KEY_EQUALS },
    { "59u",     KEY_SEMICOLON },
    { "39u",     KEY_APOSTROPHE },
    { "44u",     KEY_COMMA },
    { "46u",     KEY_PERIOD },
    { "47u",     KEY_SLASH },
    { "92u",     KEY_BACKSLASH },
    { "96u",     KEY_BACKTICK },
    { "91u",     KEY_OPEN_BRACKET },
    { "93u",     KEY_CLOSE_BRACKET },

    // Arrow keys
    { "1A",      KEY_UP },
    { "1B",      KEY_DOWN },
    { "1C",      KEY_RIGHT },
    { "1D",      KEY_LEFT },

    // Function keys
    { "1P",      KEY_F1 },
    { "1Q",      KEY_F2 },
    { "13~",     KEY_F3 },
    { "1S",      KEY_F4 },
    { "15~",     KEY_F5 },
    { "17~",     KEY_F6 },
    { "18~",     KEY_F7 },
    { "19~",     KEY_F8 },
    { "20~",     KEY_F9 },
    { "21~",     KEY_F10 },
    { "23~",     KEY_F11 },
    { "24~",     KEY_F12 },

    // Special keys
    { "27u",     KEY_ESCAPE },
    { "9u",      KEY_TAB },
    { "57358u",  KEY_CAPS_LOCK },
    { "13u",     KEY_ENTER },
    { "32u",     KEY_SPACE },
    { "8u",      KEY_BACKSPACE },
    { "3~",      KEY_DELETE },
    { "2~",      KEY_INSERT },
    { "1H",      KEY_HOME },
    { "1F",      KEY_END },
    { "5~",      KEY_PAGE_UP },
    { "6~",      KEY_PAGE_DOWN },
    { "57442u",  KEY_CTRL_LEFT },
    { "57448u",  KEY_CTRL_RIGHT },
    { "57441u",  KEY_SHIFT_LEFT },
    { "57447u",  KEY_SHIFT_RIGHT },
    { "57443u",  KEY_ALT_LEFT },
    { "57449u",  KEY_ALT_RIGHT },
    { "57444u",  KEY_SUPER_LEFT },
    { "57450u",  KEY_SUPER_RIGHT },

    // Numpad keys (Num Lock OFF)
    { "57425u",  KEY_NUMPAD_INS },
    { "57424u",  KEY_NUMPAD_END },
    { "57420u",  KEY_NUMPAD_DOWN },
    { "57422u",  KEY_NUMPAD_PG_DN },
    { "57417u",  KEY_NUMPAD_LEFT },
    { "57427u",  KEY_NUMPAD_CENTER },
    { "57418u",  KEY_NUMPAD_RIGHT },
    { "57423u",  KEY_NUMPAD_HOME },
    { "57419u",  KEY_NUMPAD_UP },
    { "57421u",  KEY_NUMPAD_PG_UP },
    { "57426u",  KEY_NUMPAD_DEL },

    // Numpad keys (Num Lock ON)
    { "57399u",  KEY_NUMPAD_0 },
    { "57400u",  KEY_NUMPAD_1 },
    { "57401u",  KEY_NUMPAD_2 },
    { "57402u",  KEY_NUMPAD_3 },
    { "57403u",  KEY_NUMPAD_4 },
    { "57404u",  KEY_NUMPAD_5 },
    { "57405u",  KEY_NUMPAD_6 },
    { "57406u",  KEY_NUMPAD_7 },
    { "57407u",  KEY_NUMPAD_8 },
    { "57408u",  KEY_NUMPAD_9 },
    { "57409u",  KEY_NUMPAD_DOT },

    // Numpad operation keys
    { "57410u",  KEY_NUMPAD_DIVIDE },
    { "57411u",  KEY_NUMPAD_MULTIPLY },
    { "57412u",  KEY_NUMPAD_MINUS },
    { "57413u",  KEY_NUMPAD_PLUS },
    { "57414u",  KEY_NUMPAD_ENTER },
    { "57360u",  KEY_NUM_LOCK },
    
    // End sentinel
    { NULL, KEY_UNKNOWN }
};

// Convert key code string to KeyCode enum
KeyCode key_code_from_string(const char* key_str) {
    if (!key_str) {
        return KEY_UNKNOWN;
    }
    
    for (int i = 0; KEY_CODE_MAPPINGS[i].code != NULL; i++) {
        if (strcmp(KEY_CODE_MAPPINGS[i].code, key_str) == 0) {
            return KEY_CODE_MAPPINGS[i].key;
        }
    }
    
    printf("Unknown key code: %s\n", key_str);
    return KEY_UNKNOWN;
}

// Get display string for key code
const char* key_code_to_string(KeyCode key_code) {
    static char buffer[32];
    
    switch (key_code) {
        case KEY_A: return "A";
        case KEY_B: return "B";
        case KEY_C: return "C";
        case KEY_D: return "D";
        case KEY_E: return "E";
        case KEY_F: return "F";
        case KEY_G: return "G";
        case KEY_H: return "H";
        case KEY_I: return "I";
        case KEY_J: return "J";
        case KEY_K: return "K";
        case KEY_L: return "L";
        case KEY_M: return "M";
        case KEY_N: return "N";
        case KEY_O: return "O";
        case KEY_P: return "P";
        case KEY_Q: return "Q";
        case KEY_R: return "R";
        case KEY_S: return "S";
        case KEY_T: return "T";
        case KEY_U: return "U";
        case KEY_V: return "V";
        case KEY_W: return "W";
        case KEY_X: return "X";
        case KEY_Y: return "Y";
        case KEY_Z: return "Z";
        
        case KEY_NUM0: return "0";
        case KEY_NUM1: return "1";
        case KEY_NUM2: return "2";
        case KEY_NUM3: return "3";
        case KEY_NUM4: return "4";
        case KEY_NUM5: return "5";
        case KEY_NUM6: return "6";
        case KEY_NUM7: return "7";
        case KEY_NUM8: return "8";
        case KEY_NUM9: return "9";
        
        case KEY_MINUS: return "Minus";
        case KEY_EQUALS: return "Equals";
        case KEY_SEMICOLON: return "Semicolon";
        case KEY_APOSTROPHE: return "Apostrophe";
        case KEY_COMMA: return "Comma";
        case KEY_PERIOD: return "Period";
        case KEY_SLASH: return "Slash";
        case KEY_BACKSLASH: return "Backslash";
        case KEY_BACKTICK: return "Backtick";
        case KEY_OPEN_BRACKET: return "OpenBracket";
        case KEY_CLOSE_BRACKET: return "CloseBracket";
        
        case KEY_UP: return "Up";
        case KEY_DOWN: return "Down";
        case KEY_RIGHT: return "Right";
        case KEY_LEFT: return "Left";
        
        case KEY_F1: return "F1";
        case KEY_F2: return "F2";
        case KEY_F3: return "F3";
        case KEY_F4: return "F4";
        case KEY_F5: return "F5";
        case KEY_F6: return "F6";
        case KEY_F7: return "F7";
        case KEY_F8: return "F8";
        case KEY_F9: return "F9";
        case KEY_F10: return "F10";
        case KEY_F11: return "F11";
        case KEY_F12: return "F12";
        
        case KEY_ESCAPE: return "Escape";
        case KEY_TAB: return "Tab";
        case KEY_CAPS_LOCK: return "CapsLock";
        case KEY_ENTER: return "Enter";
        case KEY_SPACE: return "Space";
        case KEY_BACKSPACE: return "Backspace";
        case KEY_DELETE: return "Delete";
        case KEY_INSERT: return "Insert";
        case KEY_HOME: return "Home";
        case KEY_END: return "End";
        case KEY_PAGE_UP: return "PageUp";
        case KEY_PAGE_DOWN: return "PageDown";
        case KEY_CTRL_LEFT: return "ControlLeft";
        case KEY_CTRL_RIGHT: return "ControlRight";
        case KEY_SHIFT_LEFT: return "ShiftLeft";
        case KEY_SHIFT_RIGHT: return "ShiftRight";
        case KEY_ALT_LEFT: return "AltLeft";
        case KEY_ALT_RIGHT: return "AltRight";
        case KEY_SUPER_LEFT: return "SuperLeft";
        case KEY_SUPER_RIGHT: return "SuperRight";
        
        case KEY_NUMPAD_INS: return "NumpadIns";
        case KEY_NUMPAD_END: return "NumpadEnd";
        case KEY_NUMPAD_DOWN: return "NumpadDown";
        case KEY_NUMPAD_PG_DN: return "NumpadPgDn";
        case KEY_NUMPAD_LEFT: return "NumpadLeft";
        case KEY_NUMPAD_CENTER: return "NumpadCenter";
        case KEY_NUMPAD_RIGHT: return "NumpadRight";
        case KEY_NUMPAD_HOME: return "NumpadHome";
        case KEY_NUMPAD_UP: return "NumpadUp";
        case KEY_NUMPAD_PG_UP: return "NumpadPgUp";
        case KEY_NUMPAD_DEL: return "NumpadDel";
        
        case KEY_NUMPAD_0: return "Numpad0";
        case KEY_NUMPAD_1: return "Numpad1";
        case KEY_NUMPAD_2: return "Numpad2";
        case KEY_NUMPAD_3: return "Numpad3";
        case KEY_NUMPAD_4: return "Numpad4";
        case KEY_NUMPAD_5: return "Numpad5";
        case KEY_NUMPAD_6: return "Numpad6";
        case KEY_NUMPAD_7: return "Numpad7";
        case KEY_NUMPAD_8: return "Numpad8";
        case KEY_NUMPAD_9: return "Numpad9";
        case KEY_NUMPAD_DOT: return "NumpadDot";
        
        case KEY_NUMPAD_DIVIDE: return "NumpadDivide";
        case KEY_NUMPAD_MULTIPLY: return "NumpadMultiply";
        case KEY_NUMPAD_MINUS: return "NumpadMinus";
        case KEY_NUMPAD_PLUS: return "NumpadPlus";
        case KEY_NUMPAD_ENTER: return "NumpadEnter";
        case KEY_NUM_LOCK: return "NumLock";
        
        case KEY_UNKNOWN:
        default:
            sprintf(buffer, "Unknown(%d)", key_code);
            return buffer;
    }
}