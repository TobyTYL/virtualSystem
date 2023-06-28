#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "filesystem.h"
#include "utils.h"
#include "cli.h"

// array is a pointer to an array of 255 char arrays
void parse_input(char *const input, char (*array)[255], int *number);
void usage();

int main()
{
	// FileSystem: (Object* root; Object* current)
	FileSystem fs;
	// bool init_fs
	if (!init_fs(&fs))
	{
		fprintf(stderr, "Error: init_fs()\n");
		exit(1);
	}

	// initialize the file system variable
	char user_input[BUFFER_MAX];
	char array[255][255];
	int element_num = 0;
	char *cmd;
	char path[255];
	while (1)
	{
		// initialize the path
		memset(path, 0, 255);
		// get the current path by using pwd command
		pwd_fs(&fs, path);
		// how many user input
		element_num = 0;
		memset(array, 0, 255 * 255);

		// prefix
		printf("\033[1;32m%s@%s\033[0m:\033[1;34m%s\033[0m%s ",
			   USERNAME,
			   MACHINE,
			   path,
			   PROMPT);

		// a b
		// user_input is an array
		readline(user_input);
		// change the element_num, array, user_input
		// array got update
		parse_input(user_input, array, &element_num);

		// user input is empty
		if (element_num == 0)
		{
			continue;
		}

		// get the first element
		cmd = array[0];
		// exit
		if (strcmp(cmd, CMD_EXIT) == 0)
		{
			// exit
			exit(0);
		}

		// cmd: cd
		else if (strcmp(cmd, CMD_CD) == 0)
		{
			// cd
			if (element_num == 2)
			{
				// if cd_fs true, then this is error
				if (!cd_fs(&fs, array[1]))
				{
					printf("Error: cd failed\n");
				}
			}
		}

		// cmd:echo
		else if (strcmp(cmd, CMD_ECHO) == 0)
		{
			// if element_num < 2, that's mean there is no file name
			if (element_num < 2)
			{
				printf("Error: echo");
				continue;
			}
			echo_fs(&fs, array[1]);
		}

		// cmd: help
		else if (strcmp(cmd, CMD_HELP) == 0)
		{
			usage();
		}

		// cmd: ls
		else if (strcmp(cmd, CMD_LS) == 0)
		{

			ls_fs(&fs);
		}

		// cmd: mkdir
		else if (strcmp(cmd, CMD_MKDIR) == 0)
		{
			if (element_num < 2)
			{
				printf("Error: mkdir\n");
				continue;
			}

			mkdir_fs(&fs, array[1]);
		}

		// cmd: pwd
		else if (strcmp(cmd, CMD_PWD) == 0)
		{
			printf("%s\n", path);
		}

		// cmd: rm
		else if (strcmp(cmd, CMD_RM) == 0)
		{

			if (element_num < 2)
			{
				printf("Error: rm\n");
				continue;
			}

			for (int i = 1; i < element_num; i++)
			{
				if (!rm_fs(&fs, array[i]))
				{
					printf("Error: rm %s failed.\n", array[i]);
				}
			}
		}
		else
		{
			printf("%s: command not found.\n", cmd);
		}
	}
}

// This function is to parse the input string into the array
void parse_input(char *const input, char (*array)[255], int *number)
{

	// 返回分隔符之前字符串的首地址
	// strtok函数会找到str中的分隔符标记，并将其换成\0，返回该字符串的首地址
	// strtok函数的第一个参数为NULL，函数将在之前strtok记住的分隔符的位置开始，查找下一个标记
	// 如果找不到空格隔行符，返回NULL
	char *token = strtok(input, " ");

	while (token != NULL)
	{
		strcpy(array[(*number)++], token);
		// update token
		token = strtok(NULL, " ");
	}
}

void usage()
{
	printf("Virtual File System 0.1\n");
}