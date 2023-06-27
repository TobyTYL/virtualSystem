#include "utils.h"

size_t readline(char* buffer) {

	size_t size = 0;

	char c;
	c = getchar();

	while (c!='\n') {
		if (c == EOF) {
			break;
		}

		buffer[size++] = c;
		c = getchar();

	}

	buffer[size] = '\0';

	return size;

}

