#include "utils.h"

// buffer is an array of 255 chars
size_t readline(char* buffer) {

	size_t size = 0;
	char c;
	// 获取一个字符
	c = getchar();

	while (c!='\n') {
		if (c == EOF) {
			break;
		}
		// save the user input into the buffer
		buffer[size++] = c;
		// next user input
		c = getchar();
	}

	buffer[size] = '\0';
	return size;
}

