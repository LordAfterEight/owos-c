#include "timer.h"
#include "std.h"
#include "rendering.h"
#include "shell_definitions.h"
#include "idt.h"

volatile unsigned long ticks = 0;

void pit_init(struct Shell* shell, uint32_t frequency) {
    uint16_t divisor = (uint16_t)(PIT_FREQ / frequency);
    outb(PIT_CMD, 0x36);          // channel 0, lobyte/hibyte, mode 3
    outb(PIT_CHANNEL0, divisor & 0xFF);
    outb(PIT_CHANNEL0, divisor >> 8);
    char buf[64];
    format(buf, "Initialized Programmable Interval Timer with frequency %dHz", frequency);
    shell_print(shell, "Kernel=>PIT:", 0xFFFFFF, false);
    shell_println(shell, buf, 0xAAAAAA, false);
}

__attribute__((interrupt))
void timer_callback(void *frame) {
    ticks++;
    outb(0x20, 0x20);
}
