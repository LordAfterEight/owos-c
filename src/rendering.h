#ifndef RENDERING_H
#define RENDERING_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern volatile uint32_t* global_framebuffer;

void blit_pixel(int x, int y, uint32_t color);
void draw_rect_f(int x, int y, int w, int h, uint32_t color);
void draw_text(int x, int y, const char* text, uint32_t color, bool inverse);
void draw_char(int x, int y, const char character, uint32_t color, bool inverse);

#endif
