#include "prerequisites.h"
#include "rendering.h"

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

    draw_text(framebuffer->address, 100, 100, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 0x77ff77);
    draw_text(framebuffer->address, 100, 110, "abcdefghijklmnopqrstuvwxyz", 0x77ff77);
    draw_text(framebuffer->address, 100, 120, "!\"%&/()[]=+*#'-_.:,;<>", 0x77ff77);

    hcf();
}
