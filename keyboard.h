#pragma once

#include <stdbool.h>
#include "event.h"

// Function to enable Kitty keyboard protocol
void enable_keyboard();

// Function to disable Kitty keyboard protocol
void disable_keyboard();

// Check if bytes represent a keyboard event
bool is_keyboard_event(const unsigned char* bytes, int length);

// Parse keyboard event from bytes
KeyEventData parse_keyboard_event(const unsigned char* bytes, int length);