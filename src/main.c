#include "prerequisites.h"
#include "rendering.h"
#include "std.h"
#include "shell.h"
#include "timer.h"
#include "idt.h"
#include "pic.h"

static void hcf(void) {
    for (;;) {
        asm ("hlt");
    }
}

void kmain(void) {
    if (LIMINE_BASE_REVISION_SUPPORTED(limine_base_revision) == false) {
        hcf();
    }

    if (framebuffer_request.response == NULL
     || framebuffer_request.response->framebuffer_count < 1) {
        hcf();
    }

    struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

    global_framebuffer = (volatile uint32_t*)framebuffer->address;

    struct InputBuffer input_buffer = {
        buffer: {' '},
        buffer_pos: 0,
    };

    struct Cursor cursor = {
        pos_x: 1,
        pos_y: 1,
        visible: true,
        last_toggle: ticks,
    };

    struct Shell shell = {
        buffer: input_buffer,
        cursor: cursor,
    };

    pic_remap();

    for (int i = 0; i < 256; i++) {
        set_idt_entry(&shell, i, default_handler, 0, 0x8E);
    }

    set_idt_entry(&shell, 32, timer_callback, 0, 0x8E);
    set_idt_entry(&shell, 14, page_fault_handler, 1, 0x8F);

    idt_init();

    outb(PIC1_DATA, 0xFF);
    outb(PIC2_DATA, 0xFF);

    outb(PIC1_DATA, inb(PIC1_DATA) & ~(1 << 0));

    pit_init(&shell, 100);

    shell_println(&shell, "", 0x000000, false);

    shell_println(&shell, "Welcome to the OwOS-C kernel!", 0x66FF66, false);
    shell_println(&shell, "Ver 0.1.0", 0xFF6666, false);
    shell_print(&shell, "Build date: ", 0xDDDDDD, false);
    shell_println(&shell, __DATE__, 0x6666FF, false);
    shell_println(&shell, "", 0xFFFFFF, false);

    int result = start_shell(shell);
    switch (result) {
        case 1: panic(" Shell crashed with exit code 1");
        case 0: hcf();
        default: panic(" Invalid return code ");
    }
}
