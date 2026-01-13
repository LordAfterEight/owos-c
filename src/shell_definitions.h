#include "rendering.h"
#include "keyboard.h"
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

void push_char(struct InputBuffer* buffer, const char character) {
    buffer->buffer[buffer->buffer_pos] = character;
    buffer->buffer_pos++;
}

void move_cursor(struct Cursor* cursor, int8_t value) {
    cursor->pos_x += value;
}

void shell_print(struct Shell* shell, char* text, uint32_t color, bool invert) {
    draw_text(shell->cursor.pos_x, shell->cursor.pos_y, text, color, invert);
    move_cursor(&shell->cursor, (strlen(text) + 1) * 7);
}

void shell_println(struct Shell* shell, char* text, uint32_t color, bool invert) {
    shell_print(shell, text, color, invert);
    shell->cursor.pos_y += 10;
    shell->cursor.pos_x = 1;
}

void handle_input(struct Shell* shell, char* input) {
    shell->cursor.pos_y += 10;
    shell->cursor.pos_x = 1;
    if (strcmp(input, "help")) {
        shell_println(shell, " - help: prints this message", 0xAAAAAA, false);
        shell_println(shell, " - clear: clears the screen", 0xAAAAAA, false);
        shell_println(shell, " - panic: makes the kernel panic", 0xFFAAAA, false);
        shell_println(shell, " - reboot: reboots the PC", 0xAAAAAA, false);
    }
    else if (strcmp(input, "panic")) {
        panic(" Induced panic ");
    }
    else if (strcmp(input, "reboot")) {
        outb(0x64, 0xFE);
    }
    else if (strcmp(input, "clear")) {
        draw_rect_f(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, 0x000000);
        shell->cursor.pos_x = 1;
        shell->cursor.pos_y = 1;
    }
    else {
        if (strcmp(input, "\0") != true) {
            shell_print(shell, "Invalid command: ", 0xFFAAAA, false);
            shell_println(shell, input, 0xAAAAAA, false);
        }
    }
}

void update_buffer(struct Shell* shell) {
    char c = getchar_polling();
    if (c) {
        if (c == '\n' || c == '\r') {
            push_char(&shell->buffer, '\0');
            draw_char(shell->cursor.pos_x, shell->cursor.pos_y + 10, '^', 0x000000, false);
            handle_input(shell, shell->buffer.buffer);
            memset(shell->buffer.buffer, 0, sizeof shell->buffer.buffer);
            shell->buffer.buffer_pos = 0;
            shell->cursor.pos_x = 1;
            shell_print(shell, "Command: ", 0xAAAAAA, false);
        } else if (c == '\b') {
            if (shell->cursor.pos_x != 0 && shell->buffer.buffer_pos != 0) {
                shell->buffer.buffer_pos -= 1;
                draw_char(shell->cursor.pos_x, shell->cursor.pos_y + 10, '^', 0x000000, false);
                shell->cursor.pos_x -= 7;
                draw_char(shell->cursor.pos_x, shell->cursor.pos_y, shell->buffer.buffer[shell->buffer.buffer_pos], 0x000000, false);
                shell->buffer.buffer[shell->buffer.buffer_pos] = 0;
            }
        } else {
            push_char(&shell->buffer, c);
            draw_char(shell->cursor.pos_x, shell->cursor.pos_y + 10, '^', 0x000000, false);
            draw_char(shell->cursor.pos_x, shell->cursor.pos_y, shell->buffer.buffer[shell->buffer.buffer_pos - 1], 0xFFFFFF, false);
            move_cursor(&shell->cursor, 7);
        }
    }
}

void update_cursor(struct Cursor* cursor) {
    if (ticks - cursor->last_toggle >= 50) {
        cursor->last_toggle = ticks;
        cursor->visible = !cursor->visible;

        char c = cursor->visible ? '^' : ' ';
        draw_char(cursor->pos_x, cursor->pos_y, c, 0xFFFFFF, false);
    }
}


void update_shell(struct Shell* shell) {
    update_buffer(shell);
    update_cursor(&shell->cursor);
}

