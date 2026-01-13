#include "idt.h"
#include <stdint.h>

void set_idt_entry(int vector, void* handler) {
    uint64_t addr = (uint64_t)handler;
    idt[vector].offset_low  = addr & 0xFFFF;
    idt[vector].selector    = 0x08;  // kernel code segment
    idt[vector].ist         = 0;
    idt[vector].type_attr   = 0x8E;  // interrupt gate, present
    idt[vector].offset_mid  = (addr >> 16) & 0xFFFF;
    idt[vector].offset_high = (addr >> 32) & 0xFFFFFFFF;
    idt[vector].zero        = 0;
}

void idt_init() {
    idt_ptr.limit = sizeof(idt) - 1;
    idt_ptr.base = (uint64_t)&idt;
    asm volatile("lidt %0" : : "m"(idt_ptr));
}

struct IDTEntry idt[256];
struct IDTPointer idt_ptr;
