#include "shell.h"

/**
 * show_help - Provides help information
 * @info: Structure containing potential arguments
 * Return: Always 0
 */
int show_help(info_t *info)
{
	char **arg_array = info->argv;

	_puts("Help: This function provides help information.\n");
	if (0)
	{
		_puts(*arg_array); /* Temporary att_unused workaround */
	}
	return (0);
}

/**
 * change_directory - Changes the current directory of the process
 * @info: Structure containing potential arguments
 * Return: Always 0
 */
int change_directory(info_t *info)
{
	char buffer[1024];
	char *cwd = getcwd(buffer, 1024);
	int chdir_ret;

	if (!cwd)
	{
		_puts("TODO: >>getcwd failure emsg here<<\n");
		return (1);
	}

	if (!info->argv[1])
		info->argv[1] = _getenv(info, "HOME=") ?: _getenv(info, "PWD=");

	if (_strcmp(info->argv[1], "-") == 0)
	{
		char *prev_dir = _getenv(info, "OLDPWD=");

		if (!prev_dir)
		{
			_puts(cwd);
			_putchar('\n');
			return (0);
		}
		_puts(prev_dir);
		_putchar('\n');
		chdir_ret = chdir(prev_dir);
	}
	else
	{
		chdir_ret = chdir(info->argv[1]);
	}

	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]);
		_eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", cwd);
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}


/**
 * exit_shell - Exits the shell
 * @info: Structure containing potential arguments
 * Return: Exits the shell with a given exit status
 * (0) if info->argv[0] != "exit"
 */
int exit_shell(info_t *info)
{
	int exitcheck;

	if (!info->argv[1])
	{
		info->err_num = -2;
	}
	else
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
	}
	return (-2);
}

