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
	char **tokens, *full_cmd;
	extern char **environ;
	int token_count, i;
	pid_t cmd_pid;

	token_count = 0;
	tokens = tokenize_cmd(cmd, " ", &token_count);
	if (strcmp(tokens[0], "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}
	else if(strcmp(tokens[0], "env") == 0)
	{
		for (i = 0; environ[i] != NULL; i++)
		{
			_print(environ[i]);
			_print("\n");
		}
	}
	else
	{
		cmd_pid = fork();
		if (cmd_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (cmd_pid == 0)
		{
			/*cmd process execution*/
			full_cmd = get_cmd_path(tokens[0]);
			if (full_cmd != NULL)
			{
				execve(full_cmd, tokens, NULL);
				perror("./shell");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			/* parent process execution*/
			wait(NULL);
		}
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
