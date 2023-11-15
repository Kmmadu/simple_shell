#include "shell.h"
void get_shell_env(void);

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
 * @prog_name: program's name
 *
 * Return: void nothing
 */
void command_exec(char *cmd, char *prog_name)
{
	char **tokens, *full_cmd, *cmd_0;
	int token_count;
	pid_t cmd_pid;

	token_count = 0;
	tokens = tokenize_cmd(cmd, " ", &token_count);
	cmd_0 = tokens[0];
	if (_strcmp(cmd_0, "exit") == 0)
		exit(EXIT_SUCCESS);
	else if (_strcmp(cmd_0, "env") == 0)
		get_shell_env();
	else
	{
		cmd_pid = fork();
		if (cmd_pid == -1)
		{
			perror(prog_name);
			exit(EXIT_FAILURE);
		}
		else if (cmd_pid == 0)
		{/*cmd process execution*/
			full_cmd = get_cmd_path(tokens[0]);
			if (full_cmd != NULL)
			{
				execve(full_cmd, tokens, NULL);
				perror(prog_name);
				exit(EXIT_FAILURE);
			}
			else
			{
				perror(prog_name);
				exit(EXIT_FAILURE);
			}
		}
		else
		{/* parent process execution*/
			wait(NULL);
		}
	}
}

/**
 * get_shell_env - get the environment varaiables
 *
 * Return: void
 */
void get_shell_env(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		_print(environ[i]);
		_print("\n");
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
			_print("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("Error while reading input.");
			exit(EXIT_FAILURE);
		}
	}
	cmd[strcspn(cmd, "\n")] = '\0';
}
