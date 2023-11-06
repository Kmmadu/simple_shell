#include "_shell.h"

/**
 * main - entry point
 *
 * Return: Always 0
 */
int main(void)
{
	while (1)
	{
		char cmd[128];

		display_prompt();
		read_cmd(cmd, sizeof(cmd));
		command_exec(cmd);
	}
	return (0);
}

