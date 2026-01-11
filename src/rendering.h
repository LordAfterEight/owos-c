#include "bitmap_font.h"
#include "std.h"

static int SCREEN_WIDTH = 1280;
static int SCREEN_HEIGHT = 720;

void blit_pixel(int fb_ptr[], int x, int y, int color) {
    fb_ptr[y * SCREEN_WIDTH + x] = color;
}

void draw_rect_f(int fb_ptr[], int x, int y, int w, int h, int color) {
    for (int pixel_y = 0; pixel_y <= h; pixel_y++) {
        for (int pixel_x = 0; pixel_x <= w; pixel_x++) {
            blit_pixel(fb_ptr, x + pixel_x, y + pixel_y, color);
        }
    }
}

void draw_text(int fb_ptr[], int x, int y, const char text[], int color) {
    int char_offset = 0;
    for (size_t character = 0; character <= strlen(text); character++) {
        const int* bitmap = get_bitmap(text[character]);
        for (int char_y = 0; char_y <= 7; char_y++) {
            for (int char_x = 7; char_x >= 0; char_x--) {
                if ((bitmap[char_y] & (1 << (7 - char_x))) != 0) {
                    blit_pixel(fb_ptr, x + ((char_x*-1) + char_offset), y + char_y, color);
                }
            }
        }
        char_offset += 8;
    }
}
