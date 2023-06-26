#include <stdlib.h>
#include <stdio.h>
#include "filesystem.h"
#include <string.h>
#include "utils.h"
#include "cil.h"

void parse_input(char *const input, char (*array)[255], int *number);

int main()
{
    FileSystem fs;
    init_fs(&fs);
    if (!init_fs(&fs))
    {
        fprintf(stderr, "Error: malloc failed in initFileSystem\n");
        exit(EXIT_FAILURE);
    }
    printf("Welcome to the file system!\n");

    char user_input[255];
    char array[255][255];
    int element_num = 0;
    char *cmd;
    while (1)
    {
        element_num = 0;
        memset(array, 0, sizeof(char) * 255 * 255);
        printf(">>>");
        readline(user_input);
        printf("You entered: %s\n", user_input);
        parse_input(user_input, array, &element_num);

        for (int i = 0; i < element_num; i++)
        {
            printf("%s\n", array[i]);
        }
        if (element_num == 0)
        {
            // enter nothing
            continue;
        }
        // first element is the command
        cmd = array[0];
        printf("cmd: %s\n", cmd);

        if (strcmp(cmd, CMD_EXIT) == 0)
        {
            exit(0);
            // exit
        }
        else if (strcmp(cmd, CMD_CD) == 0)
        {
            // cd
        }
        else if (strcmp(cmd, CMD_ECHO) == 0)
        {
            // echo
        }
        else if (strcmp(cmd, CMD_HELP) == 0)
        {
            // help
        }
        else if (strcmp(cmd, CMD_LS) == 0)
        {
            // ls
        }
        else if (strcmp(cmd, CMD_MKDIR) == 0)
        {
            // mkdir
        }
        else if (strcmp(cmd, CMD_RM) == 0)
        {
            // RM
        }
        else
        {
            printf("%s: Command not found\n", cmd);
        }
    }
}

// slice the input into tokens
void parse_input(char *const input, char (*array)[255], int *number)
{

    char *token = strtok(input, " ");
    // strcpy(array[*number++], token);

    while (token != NULL)
    {
        strcpy(array[(*number)++], token);
        token = strtok(NULL, " ");
    }
}
