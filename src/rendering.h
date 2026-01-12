#ifndef RENDERING_H
#define RENDERING_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

void blit_pixel(uint32_t* fb_ptr, int x, int y, uint32_t color);
void draw_rect_f(uint32_t* fb_ptr, int x, int y, int w, int h, uint32_t color);
void draw_text(uint32_t* fb_ptr, int x, int y, const char* text, uint32_t color, bool inverse);
void draw_char(uint32_t* fb_ptr, int x, int y, const char character, uint32_t color, bool inverse);

#endif
