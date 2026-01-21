#ifndef RAMFS
#define RAMFS

#include <stdint.h>

#define MAX_FILE_DATA 65536
#define MAX_FILES 64
#define MAX_FOLDERS 16
#define MAX_NAME_LENGTH 32
#define MAX_TOTAL_FOLDERS 64



struct File {
    const char* name;
    uint8_t length;
    uint32_t data_pointer;
    uint8_t* data;
};

struct Folder {
    char* name;
    uint8_t file_pointer;
    uint8_t folder_pointer;
    struct File* files[MAX_FILES];
    struct Folder* folders[MAX_FOLDERS];
};

void root_init(struct Folder* root_dir);
struct File* new_file(char* name);
struct Folder* new_folder(char* name);

extern volatile struct Folder root_dir;
static struct File file_pool[MAX_FILES];
static uint8_t file_data_pool[MAX_FILES][MAX_FILE_DATA];
static uint8_t file_pool_used = 0;
static struct Folder folder_pool[MAX_TOTAL_FOLDERS];
static uint8_t folder_pool_used = 0;

#endif

