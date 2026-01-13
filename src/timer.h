#pragma once
#include <stdint.h>

#define PIT_CHANNEL0 0x40
#define PIT_CMD      0x43
#define PIT_FREQ     1193182

extern volatile unsigned long ticks;

void pit_init(uint32_t frequency);
__attribute__((interrupt))
void timer_callback(void* frame);
