#ifndef FONT
#define FONT

#include <stdint.h>

struct Font {
    const char* name;
    const uint8_t height;
    const uint8_t width;
    const uint8_t* bitmaps;
};

#endif
