#ifndef __FILE_SYSTEM_H_
#define __FILE_SYSTEM_H_
#include <string.h>
#define NAME_SIZE 255
#define BUFFER_MAX 255
#include <stdbool.h>

enum object_type
{
    TYPE_FILE = 1,
    TYPE_DIR
};
typedef enum fs_error
{
    SUCCESS = 0,
    FAILED,
    EXISTED,
    NOT_FOUND,
} fs_status;

typedef struct object_s
{
    char name[NAME_SIZE];
    enum object_type type;
    size_t size;

    struct object_s *contents;
    struct object_s *next;

} Object;

typedef struct filesystem_s
{
    Object *root;
    Object *current;
} FileSystem;

bool init_fs(FileSystem *fs);
bool mkdir_fs(FileSystem *fs, char *const name);
void ls_fs(FileSystem *fs);

Object *search_object(Object *current, char *const name, enum object_type type);
#endif
