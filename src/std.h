#ifndef STD_H
#define STD_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

void panic(const char message[]);
size_t strlen(const char s[]);
bool strcmp(const char* a, const char* b);
uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t val);
void outw(uint16_t port, uint16_t val);
void *memcpy(void *restrict dest, const void *restrict src, size_t n);
void *memset(void *se, int c, size_t n);
void *memmove(void *dest, const void *src, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);

#endif
