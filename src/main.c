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
    shell_print(&shell, "Kernel: ", 0xAAAAAA, false);
    shell_println(&shell, "Setting up interrupt descrtiptor table entry for timer", 0xFFFFFF, false);
    set_idt_entry(32, timer_callback);

    shell_print(&shell, "Kernel: ", 0xAAAAAA, false);
    shell_println(&shell, "Initializing interrupt descrtiptor table", 0xFFFFFF, false);
    idt_init();

    shell_print(&shell, "Kernel: ", 0xAAAAAA, false);
    shell_println(&shell, "Initializing programmable interval timer with 100Hz", 0xFFFFFF, false);
    pit_init(100);

    shell_print(&shell, "Kernel: ", 0xAAAAAA, false);
    shell_println(&shell, "Enabling interrupts", 0xFFFFFF, false);
    asm volatile("sti");

    shell_println(&shell, "", 0x000000, false);

    shell_println(&shell, "Welcome to the OwOS-C kernel!", 0x66FF66, false);
    shell_println(&shell, "Ver 0.1.0", 0xFF6666, false);
    shell_print(&shell, "Build date: ", 0xDDDDDD, false);
    shell_println(&shell, __DATE__, 0x6666FF, false);
    shell_println(&shell, "", 0xFFFFFF, false);

    //draw_rect_f(100, 100, 100, 100, 0xFFFFFF);

    int result = start_shell(shell);
    switch (result) {
        case 1: panic(" Shell crashed with exit code 1");
        case 0: hcf();
        default: panic(" Invalid return code ");
    }
}
