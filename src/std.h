#ifndef STD_H
#define STD_H

#include <stddef.h>
#include <stdint.h>

void panic(uint32_t fb_ptr[], const char message[]);
size_t strlen(const char s[]);
bool strcmp(const char* a, const char* b);
void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);

#endif
