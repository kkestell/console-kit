#pragma once

#include "event.h"
#include <stdbool.h>

// Function to enable SGR mouse reporting
void enable_mouse();

// Function to disable SGR mouse reporting
void disable_mouse();

// Check if bytes represent a mouse event
bool is_mouse_event(const unsigned char *bytes, int length);

// Parse mouse event from bytes
MouseEventData parse_mouse_event(const unsigned char *bytes, int length);