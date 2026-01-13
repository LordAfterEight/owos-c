#pragma once
#include <stdint.h>

struct IDTEntry {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t ist;
    uint8_t type_attr;
    uint16_t offset_mid;
    uint32_t offset_high;
    uint32_t zero;
} __attribute__((packed));

struct IDTPointer {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));

extern struct IDTEntry idt[256];
extern struct IDTPointer idt_ptr;

void set_idt_entry(int vector, void* handler);
void idt_init();
extern void timer_handler_asm();
