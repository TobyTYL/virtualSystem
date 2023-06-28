#ifndef __FILE_SYSTEM_H_
#define __FILE_SYSTEM_H_

#include <string.h>
#include <stdbool.h>


enum object_type {
	TYPE_FILE = 1,
	TYPE_DIR
};

#define NAME_MAX 255
#define BUFFER_MAX 255

// 一个文件有什么元素，是文本还是目录路径（文件夹）
typedef struct object_s {
	char name[NAME_MAX];
	enum object_type type;
	size_t size;
	
	// 针对于文件夹下面有什么东西
	struct object_s* contents; //LINKED LIST

	// pointer
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
void pwd_fs(FileSystem* fs, char* path);
bool rm_fs(FileSystem* fs, char* const name);

Object* search_object(Object* current, char* const name, enum object_type type);



#endif