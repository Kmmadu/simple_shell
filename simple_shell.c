#include "shell.h"
#include <stdio.h>

/**
 * display_prompt - Display the regular prompt message.
 */
void display_prompt(void)
{
	printf("cisfun$ ");
}

/**
 * command_exec - Execute a command read in the prompt.
 * @cmd: Input command from the prompt.
 */
void command_exec(char *cmd)
{
	char **tokens;
	int token_count;

	pid_t cmd_pid = fork();

	token_count = 0;

	if (cmd_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (cmd_pid == 0)
	{
		tokens = tokenize_cmd(cmd, " ", &token_count);
		execve(tokens[0], tokens, NULL);
		perror("./shell");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
}

/**
 * read_cmd - Read the input command from the prompt.
 * @cmd: Command to be executed.
 * @size: Buffer size of the command.
 */
void read_cmd(char *cmd, size_t size)
{
	if (fgets(cmd, size, stdin) == NULL)
	{
		if (feof(stdin))
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			printf("Error while reading input.\n");
			exit(EXIT_FAILURE);
		}
	}
	cmd[strcspn(cmd, "\n")] = '\0';
}

