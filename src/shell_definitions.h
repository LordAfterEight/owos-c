#ifndef SHELL_H
#define SHELL_H

#include "rendering.h"
#include "drivers/ps2.h"
#include "timer.h"

struct InputBuffer {
    char buffer[256];
    int buffer_pos;
};

struct Cursor {
    int pos_x;
    int pos_y;
    bool visible;
    unsigned long last_toggle;
};

struct Shell {
    struct InputBuffer buffer;
    struct Cursor cursor;
};

void push_char(struct InputBuffer* buffer, const char character);
void move_cursor(struct Cursor* cursor, int8_t value);
void shell_print(struct Shell* shell, char* text, uint32_t color, bool invert);
void shell_println(struct Shell* shell, char* text, uint32_t color, bool invert);
void handle_input(struct Shell* shell, char* input);
void update_buffer(struct Shell* shell);
void update_cursor(struct Cursor* cursor);
void update_shell(struct Shell* shell);

#endif
