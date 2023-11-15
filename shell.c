#include "shell.h"

/**
 * main - entry point
 * @argc: argument count
 * @argv: arguments vector
 *
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	char *prog_name;

	(void)argc;
	prog_name = argv[0];
	while (1)
	{
		char cmd[128];

		display_prompt();
		read_cmd(cmd, sizeof(cmd));
		command_exec(cmd, prog_name);
	}
	return (0);
}

