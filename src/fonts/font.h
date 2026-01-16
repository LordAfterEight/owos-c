#ifndef FONT
#define FONT

struct Font {
    const char* name;
    const uint8_t height;
    const uint8_t width;
    const uint8_t* bitmaps;
};

#endif
