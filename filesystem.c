
#include <stdlib.h>
#include <stdio.h>

#include "filesystem.h"

Object* create_object(
	char* const name,
	enum object_type type,
	size_t size,
	struct object_s* contents) {


	Object* object;
	object = (Object*)malloc(sizeof(Object));
	if (object == NULL) {
		return NULL;
	}

	strcpy(object->name, name);
	object->type = type;
	object->size = size;

	object->contents = contents;
	object->next = NULL;
	object->parent = NULL;

	return object;
}


bool init_fs(FileSystem* fs) {

	fs->root = create_object("", TYPE_DIR, 0, NULL);

	if (fs->root == NULL) {
		return false;
	}


	fs->current = fs->root;

	return true;
}

Object* search_object(Object* current, char* const name, enum object_type type) {

	Object* p = current->contents;

	while (p != NULL) {
		if (p->type == type && strcmp(p->name, name) == 0) {
			break;
		}

		p = p->next;
	}

	return p;
}



bool mkdir_fs(FileSystem* fs, char* const name) {

	if (search_object(fs->current, name, TYPE_DIR) != NULL) {
		return false;
	}


	Object* object = create_object(name, TYPE_DIR, 0, NULL);
	if (object == NULL) {
		return false;
	}

	//文件夹为空
	if (fs->current->contents == NULL) {
		fs->current->contents = object;
		return true;
	}

	Object* p = fs->current->contents;

	while (p->next != NULL) {
		p = p->next;
	}

	object->parent = fs->current;

	p->next = object;

	return true;
}

void ls_fs(FileSystem* fs) {

	Object* p = fs->current->contents;

	while (p != NULL){
		if (p->type == TYPE_DIR) {
			printf("\033[1;32;40m%s\033[0m\t", p->name);
			
		}
		else {
			printf("%s\t", p->name);
		}
		
		p = p->next;

		if (p == NULL) {
			printf("\n");
		}
	}

}



bool echo_fs(FileSystem* fs, char* const name) {

	if (search_object(fs->current, name, TYPE_FILE) != NULL) {
		return false;
	}


	Object* object = create_object(name, TYPE_FILE, 0, NULL);
	if (object == NULL) {
		return false;
	}

	//文件夹为空
	if (fs->current->contents == NULL) {
		fs->current->contents = object;
		return true;
	}

	Object* p = fs->current->contents;

	while (p->next != NULL) {
		p = p->next;
	}
	
	object->parent = fs->current;
	p->next = object;

	return true;
}


bool cd_fs(FileSystem* fs, char* const path) {

	if (path[0] == '\0') {
		return true;
	}

	bool abspath = false;

	if (path[0] == '/') {
		abspath = true;
	}

	char* token = strtok(path, "/");

	Object* tmp;

	if (abspath) {
		tmp = fs->root;
		token = strtok(NULL, "/");
	}
	else {
		tmp = fs->current;
	}

	printf("%s\n", token);
	while (token != NULL) {

		if (strcmp(token, ".") == 0) {
			//pass
		}
		else if (strcmp(token, "..") == 0) {
			if (tmp->parent == NULL) {
				return false;
			}
			tmp = tmp->parent;
		}
		else if (token[0] == '\0') {
			//pass
		}
		else {

			Object* obj = search_object(tmp, token, TYPE_DIR);
			if (obj == NULL) {
				return false;
			}

			tmp = obj;
		}

		token = strtok(NULL, "/");
	}

	fs->current = tmp;
	return true;
}


