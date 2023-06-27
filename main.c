
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "filesystem.h"
#include "utils.h"
#include "cli.h"

void parse_input(char *const input, char (*array)[255], int *number);
void usage();

int main()
{
	FileSystem fs;
	if (!init_fs(&fs))
	{
		fprintf(stderr, "Error: init_fs()\n");
		exit(1);
	}

	char user_input[BUFFER_MAX];
	char array[255][255];
	int element_num = 0;
	char *cmd;
	while (1)
	{
		element_num = 0;
		memset(array, 0, 255 * 255);

		printf(PROMPT);
		// a b
		readline(user_input);

		parse_input(user_input, array, &element_num);

		if (element_num == 0)
		{
			// 
			continue;
		}

		cmd = array[0];

		if (strcmp(cmd, CMD_EXIT) == 0)
		{
			// exit
			exit(0);
		}
		else if (strcmp(cmd, CMD_CD) == 0)
		{
			// cd
			if (element_num == 2)
			{
				if (!cd_fs(&fs, array[1]))
				{
					printf("Error: cd");
				}
			}
		}
		else if (strcmp(cmd, CMD_ECHO) == 0)
		{
			// echo
			if (element_num < 2)
			{
				printf("Error: echo");
				continue;
			}
			echo_fs(&fs, array[1]);
		}
		else if (strcmp(cmd, CMD_HELP) == 0)
		{
			usage();
		}
		else if (strcmp(cmd, CMD_LS) == 0)
		{

			ls_fs(&fs);
		}
		else if (strcmp(cmd, CMD_MKDIR) == 0)
		{
			// mkdir
			if (element_num < 2)
			{
				printf("Error: mkdir\n");
				continue;
			}

			mkdir_fs(&fs, array[1]);
		}
		else if (strcmp(cmd, CMD_PWD) == 0)
		{
		}
		else if (strcmp(cmd, CMD_RM) == 0)
		{
		}
		else
		{
			printf("%s: command not found.\n", cmd);
		}
	}
}

void parse_input(char *const input, char (*array)[255], int *number)
{

	char *token = strtok(input, " ");
	// 
	while (token != NULL)
	{
		strcpy(array[(*number)++], token);
		token = strtok(NULL, " ");
	}
}

void usage()
{
	printf("Virtual File System 0.1\n");
}