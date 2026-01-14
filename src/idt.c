#include <stdint.h>
#include "std.h"
#include "shell_definitions.h"
#include "idt.h"

__attribute__((aligned(32)))
struct IDTEntry idt[256] __attribute__((aligned(16)));

__attribute__((aligned(32)))
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

    char buf[80];
    format(buf, "Set up entry for Interrupt Descriptor Table at vector 0x%x", vector);
    shell_print(shell, "Kernel=>IDT:", 0xFFFFFF, false);
    shell_println(shell, buf, 0xAAAAAA, false);
}

void idt_init(void) {
    idt_ptr.limit = sizeof(idt) - 1;
    idt_ptr.base  = (uint64_t)&idt;

    asm volatile("lidt %0" : : "m"(idt_ptr) : "memory");
}

__attribute__((interrupt))
void default_handler(struct InterruptFrame *frame) {
    panic(" Unhandled interrupt ");
}

__attribute__((interrupt))
void page_fault_handler(struct InterruptFrame *frame, uintptr_t error_code) {
    panic(" Page fault ");
}
