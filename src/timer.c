#include "timer.h"
#include "std.h"
#include "rendering.h"

volatile unsigned long ticks = 0;

void pit_init(uint32_t frequency) {
    uint16_t divisor = (uint16_t)(PIT_FREQ / frequency);
    outb(PIT_CMD, 0x36);          // channel 0, lobyte/hibyte, mode 3
    outb(PIT_CHANNEL0, divisor & 0xFF);
    outb(PIT_CHANNEL0, divisor >> 8);
}

__attribute__((interrupt))
void timer_callback(void* frame) {
    ticks++;
    uint8_t eoi = 0x20;
    asm volatile("outb %0, %1" : : "a"(eoi), "Nd"(0x20));
}
