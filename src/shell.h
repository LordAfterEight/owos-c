#include "shell_definitions.h"

int start_shell(struct Shell shell) {
    shell_print(&shell, "Command: ", 0xAAAAAA, false);
    while (1) {
        update_shell(&shell);
    }
    return 0;
}
