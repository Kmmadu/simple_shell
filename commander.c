#include "shell.h"

/**
 * main_shell_loop - Main shell loop
 * @info: Pointer to the parameter and return info struct.
 * @av: The argument vector from main().
 *
 * Return: Returns 0 on success, 1 on error, or an error code.
 */
int main_shell_loop(info_t *info, char **av)
{
	ssize_t read_result;
	int builtin_ret;

	while ((read_result = get_input(info)) != -1 && (builtin_ret = find_builtin_command(info)) != -2)
	{
		clear_info(info);
		if (interactive(info))
		{
			_puts("$ ");
			_eputchar(BUF_FLUSH);
		}
		if (read_result != -1)
		{
			set_info(info, av);
			if (builtin_ret == -1)
				find_external_command(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}

	write_history(info);
	free_info(info, 1);

	if (!interactive(info) && info->status)
		exit(info->status);

	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}

	return (builtin_ret);
}

/**
 * find_builtin_command - Find a builtin command
 * @info: Pointer to the parameter and return info struct.
 *
 * Return: Returns -1 if builtin not found, 0 if builtin executed successfully,
 *         1 if builtin found but not successful, or -2 if builtin signals exit().
 */
int find_builtin_command(info_t *info)
{
	int built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (int i = 0; builtintbl[i].type; i++)
	{
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	}

	return (built_in_ret);
}
/**
 * find_external_command - Find an external command
 * @info: Pointer to the parameter and return info struct.
 */
void find_external_command(info_t *info)
{
	info->path = info->argv[0];

	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}

	int k = count_non_delimiters(info->arg);

	if (k == 0)
		return;

	char *path = find_command_in_path(info, _getenv(info, "PATH="), info->argv[0]);

	if (path)
	{
		info->path = path;
		execute_external_command(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=") || info->argv[0][0] == '/') && is_valid_command(info, info->argv[0]))
			execute_external_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

