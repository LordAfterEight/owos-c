#include <stdint.h>
#include "std.h"
#include "shell_definitions.h"
#include "idt.h"
#include "fonts/OwOSFont_8x16.h"

__attribute__((packed))
struct IDTEntry idt[256] __attribute__((aligned(16)));

__attribute__((packed))
struct IDTPointer idt_ptr __attribute__((aligned(16)));

void set_idt_entry(struct Shell* shell, int vector, void *handler, uint8_t ist, uint8_t type_attr) {
    uint64_t addr = (uint64_t)handler;

    idt[vector].offset_low  = addr & 0xFFFF;
    idt[vector].offset_mid  = (addr >> 16) & 0xFFFF;
    idt[vector].offset_high = (addr >> 32) & 0xFFFFFFFF;

    idt[vector].selector    = 0x08;
    idt[vector].ist         = ist;
    idt[vector].type_attr   = type_attr;
    idt[vector].zero        = 0;
}

void idt_init(void) {
    idt_ptr.limit = sizeof(idt) - 1;
    idt_ptr.base  = (uint64_t)&idt;

    asm volatile("lidt %0" : : "m"(idt_ptr) : "memory");
}

__attribute__((naked, used, section(".text.doublefault")))
void default_handler(void) {
    panic("Unhandleable Interrupt ocurred");
    asm volatile(
        "cli\n\t"
        "push $0\n\t"
        "push %0\n\t"
        "1: hlt\n\t"
        "jmp 1b"
        : : "i"(0xFF)
    );
}

__attribute__((naked, used, section(".text.doublefault")))
void page_fault_handler(void) {
    panic("Page Fault ocurred");
    asm volatile(
        "cli\n\t"
        "push $0\n\t"
        "push %0\n\t"
        "1: hlt\n\t"
        "jmp 1b"
        : : "i"(0xFF)
    );
}
