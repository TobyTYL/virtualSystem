#include "utils.h"
// This function is used to

size_t readline(char *buffer)
{
    size_t size = 0;
    char c;
    c = getchar();
    while ((c != '\n') && (c != EOF))
    {
        buffer[size++] = c;
        c = getchar();
    }
    buffer[size] = '\0';
    return size;
}