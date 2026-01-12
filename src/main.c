#include "prerequisites.h"
#include "std.h"
#include "shell.h"

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

    int result = start_shell(framebuffer->address);
    switch (result) {
        case 1: panic(framebuffer->address, " Shell crashed with exit code 1");
        case 0: hcf();
        default: panic(framebuffer->address, " Invalid return code ");
    }
}
