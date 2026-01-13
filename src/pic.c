#include "pic.h"
#include "std.h"
#include <stdint.h>

void pic_remap() {
    uint8_t a1 = inb(PIC1_DATA);
    uint8_t a2 = inb(PIC2_DATA);

    outb(PIC1_COMMAND, ICW1_INIT);
    outb(PIC2_COMMAND, ICW1_INIT);
    outb(PIC1_DATA, 0x20); // IDT offset 32
    outb(PIC2_DATA, 0x28); // IDT offset 40
    outb(PIC1_DATA, 4);    // Tell master about slave
    outb(PIC2_DATA, 2);    // Tell slave its cascade identity
    outb(PIC1_DATA, ICW4_8086);
    outb(PIC2_DATA, ICW4_8086);

    outb(PIC1_DATA, a1);
    outb(PIC2_DATA, a2);
}
