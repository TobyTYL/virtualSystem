#include <stdlib.h>
#include <stdio.h>

#include "filesystem.h"

Object *create_object(
	char *const name,
	enum object_type type,
	size_t size,
	Object *contents)
{
	Object *obj;
	// linklist
	obj = (Object *)malloc(sizeof(Object));
	if (obj == NULL)
	{
		return NULL;
	}

	strcpy(obj->name, name);
	obj->type = type;
	obj->size = size;

	obj->contents = contents;
	obj->next = NULL;
	obj->parent = NULL;
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

Object *search_object(Object *current, char *const name, enum object_type type)
{
	// current is an object type
	Object *p = current->contents;

	while (p != NULL)
	{
		if (p->type == type && strcmp(p->name, name) == 0)
		{
			break;
		}

		p = p->next;
	}

	return p;
}

bool mkdir_fs(FileSystem *fs, char *const name)
{

	if (search_object(fs->current, name, TYPE_DIR) != NULL)
	{
		return false;
	}

	Object *object = create_object(name, TYPE_DIR, 0, NULL);
	if (object == NULL)
	{
		return false;
	}

	// 把要添加的文件夹的父亲指向当前的文件夹
	object->parent = fs->current;

	// If current is empty folder, add the new folder to the current directory
	if (fs->current->contents == NULL)
	{
		fs->current->contents = object;
		return true;
	}

	Object *p = fs->current->contents;

	// why
	while (p->next != NULL)
	{
		p = p->next;
	}

	p->next = object;

	return true;
}

void ls_fs(FileSystem *fs)
{

	Object *p = fs->current->contents;

	/*
	for (int i = 31; i < 38; i++)
		{
			printf("\033[%dm 123456\n",i);
			//printf("\033[31m 456789\n");
		}

	*/

	while (p != NULL)
	{
		if (p->type == TYPE_DIR)
		{
			printf("\033[1;32m%s\033[0m\t", p->name);
		}
		else
		{
			printf("%s\t", p->name);
		}

		p = p->next;

		if (p == NULL)
		{
			printf("\n");
		}
	}
}

bool echo_fs(FileSystem *fs, char *const name)
{

	if (search_object(fs->current, name, TYPE_FILE) != NULL)
	{
		return false;
	}

	Object *object = create_object(name, TYPE_FILE, 0, NULL);
	if (object == NULL)
	{
		return false;
	}

	// If current is not a directory, add the file to the current directory
	if (fs->current->contents == NULL)
	{
		fs->current->contents = object;
		return true;
	}

	// why
	Object *p = fs->current->contents;

	while (p->next != NULL)
	{
		p = p->next;
	}

	object->parent = fs->current;
	p->next = object;

	return true;
}

bool cd_fs(FileSystem *fs, char *const path)
{

	// fail
	if (path[0] == '\0')
	{
		return true;
	}

	bool abspath = false;

	if (path[0] == '/')
	{
		abspath = true;
	}

	// cd 后面的路径或者文件
	char *token = strtok(path, "/");

	Object *tmp;

	// 如果开头为/，那么就是绝对路径
	if (abspath)
	{
		tmp = fs->root;
	}
	// 否则为当前路径
	else
	{
		tmp = fs->current;
	}

	while (token != NULL)
	{

		// if it is ".", do nothing
		if (strcmp(token, ".") == 0)
		{
			// pass
		}
		// if it is "..", go to parent
		else if (strcmp(token, "..") == 0)
		{
			// if the current is root, return false
			if (tmp->parent == NULL)
			{
				return false;
			}
			// otherwise just point it to its parent
			tmp = tmp->parent;
		}

		// if it is "", do nothing
		else if (token[0] == '\0')
		{
			// pass
		}

		// if it is a direction, return false
		else
		{
			Object *obj = search_object(tmp, token, TYPE_DIR);
			if (obj == NULL)
			{
				return false;
			}

			tmp = obj;
		}

		token = strtok(NULL, "/");
	}

	fs->current = tmp;
	return true;
}

void pwd_fs(FileSystem *fs, char *path)
{

	char array[255][255];
	int count = 0;

	// fs is a Filesystem type
	// tmp is the current location
	Object *tmp = fs->current;

	// if the current location is not root, copy the name to the array
	while (tmp->parent != NULL)
	{

		strcpy(array[count++], tmp->name);

		tmp = tmp->parent;
	}
	// cat the path
	strcat(path, "/");
	for (int i = count - 1; i >= 0; i--)
	{
		strcat(path, array[i]);
		if (i != 0)
		{
			strcat(path, "/");
		}
	}
}

void remove_object(Object *obj)
{

	if (obj->type == TYPE_FILE)
	{
		free(obj);
		return;
	}
	else if (obj->type == TYPE_DIR)
	{

		Object *p = obj->contents;

		while (p != NULL)
		{

			remove_object(p);

			p = p->next;
		}
		obj->contents = NULL;
	}
}

bool rm_fs(FileSystem *fs, char *const name)
{

	bool removed = false;
	Object *p = fs->current->contents;
	Object *prev = NULL;
	while (p != NULL)
	{

		if (strcmp(p->name, name) == 0)
		{

			if (prev == NULL)
			{
				fs->current->contents = p->next;
				remove_object(p);
				p = fs->current->contents;
				// prev = NULL;
			}
			else
			{
				prev->next = p->next;
				remove_object(p);
				p = prev->next;
			}
			removed = true;
		}
		else
		{
			prev = p;
			p = p->next;
		}
	}

	return removed;
}
