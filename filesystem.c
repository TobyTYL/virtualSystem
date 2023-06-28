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

	//���¸��ڵ�
	object->parent = fs->current;

	//�ļ���Ϊ��
	if (fs->current->contents == NULL) {
		fs->current->contents = object;
		return true;
	}

	Object* p = fs->current->contents;

	while (p->next != NULL) {
		p = p->next;
	}

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

	//�ļ���Ϊ��
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
	}
	else {
		tmp = fs->current;
	}

	
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


void pwd_fs(FileSystem* fs,char* path) {

	char array[255][255];
	int count = 0;

	Object* tmp = fs->current;

	while (tmp->parent != NULL) {

		strcpy(array[count++], tmp->name);

		tmp = tmp->parent;

	}

	strcat(path, "/");
	for (int i = count - 1; i >= 0; i--) {
		strcat(path, array[i]);
		if (i != 0) {
			strcat(path, "/");
		}
	}
}


void remove_object(Object* obj) {

	if (obj->type == TYPE_FILE) {
		free(obj);
		return;
	}
	else if (obj->type == TYPE_DIR) {

		Object* p = obj->contents;

		while (p != NULL) {

			remove_object(p);

			p = p->next;
		}
		obj->contents = NULL;

	}
}


bool rm_fs(FileSystem* fs, char* const name) {

	bool removed = false;
	Object* p = fs->current->contents;
	Object* prev = NULL;
	while (p != NULL) {

		if (strcmp(p->name, name) == 0) {
			
			if (prev == NULL) {
				fs->current->contents = p->next;
				remove_object(p);
				p = fs->current->contents;
				//prev = NULL;
			}
			else {
				prev->next = p->next;
				remove_object(p);
				p = prev->next;
			}
			removed = true;

		}
		else {
			prev = p;
			p = p->next;
		}
	}

	return removed;
}
