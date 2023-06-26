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
    // 当前所有的
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

// 搜索当前目录下的文件
Object *search_object(Object *current, char *const name, enum object_type type)
{
    Object *p = current->contents;
    while (p != NULL)
    {
        if (strcmp(p->name, name) == 0 && p->type == type)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

bool mkdir_fs(FileSystem *fs, char *const name)
{
    // 目录已经存在
    if (search_object(fs->current, name, TYPE_DIR) != NULL)
    {
        printf("Error: %s already exists\n", name);
        return false;
    }

    Object *obj;
    obj = create_object(name, TYPE_DIR, 0, NULL);
    if (obj == NULL)
    {
        return false;
    }

    // 当前目录节点假设为空
    if (fs->current->contents == NULL)
    {
        fs->current->contents = obj;
        return true;
    }
    Object *p = fs->current->contents;
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = obj;

    return true;
}

void ls_fs(FileSystem *fs)
{
    Object *p = fs->current->contents;
    while (p != NULL)
    {

        printf("%s ", p->name);
        p = p->next;
    }
    printf("\n");
}