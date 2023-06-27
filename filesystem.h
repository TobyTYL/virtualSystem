
#ifndef __FILE_SYSTEM_H_
#define __FILE_SYSTEM_H_

#include <string.h>
#include <stdbool.h>

#define PROMPT ">>>"


enum object_type {
	TYPE_FILE = 1,
	TYPE_DIR
};

#define NAME_MAX 255
#define BUFFER_MAX 255

typedef struct object_s {
	char name[NAME_MAX];
	enum object_type type;
	size_t size;
	
	struct object_s* contents;//LINKED LIST
	struct object_s* next;

	struct object_s* parent;

}Object;


typedef struct filesystem_s {
	Object* root;
	Object* current;
	
}FileSystem;

bool init_fs(FileSystem* fs);
bool mkdir_fs(FileSystem* fs,char* const name);
bool echo_fs(FileSystem* fs, char* const name);
void ls_fs(FileSystem* fs);
bool cd_fs(FileSystem* fs, char* const path);


Object* search_object(Object* current, char* const name, enum object_type type);






#endif