#include "filesystem.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

Object *create_object(char *const name, enum object_type type, size_t size, struct object_s *contents)
{
    Object *obj;
    obj = (Object *)malloc(sizeof(Object));
    if (obj == NULL)
    {
        return NULL;
    }
    strcpy(obj->name, name); // Name
    obj->type = type;        // Dirctionary
    obj->size = size;        // Size

    obj->contents = contents; // Contents
    return obj;
}

bool init_fs(FileSystem *fs)
{
    fs->root = create_object("", TYPE_DIR, 0, NULL);
    if (fs->root == NULL)
    {
        return false;
    }

    fs->current = fs->root;
    return true;
}