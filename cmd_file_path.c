#include "shell.h"
/**
 * get_cmd_path - get the command's file path
 * @cmd: the input command
 *
 * Return: pointer to the corresponding path or NULL if not existing
 */
char *get_cmd_path(char *cmd)
{
	char *paths, *p_cpy, *dir, *cmd_path, *existing_path;
	struct stat buf;

	paths = getenv("PATH");
	if (paths)
	{
		p_cpy = strdup(paths);
		dir = strtok(p_cpy, ":");
		while (dir != NULL)
		{
			cmd_path = construct_cmd_path(dir, cmd);
			if (cmd_path == NULL)
			{
				free(p_cpy);
				return (cmd_path);
			}

			existing_path = does_path_exists(cmd_path);
			if (existing_path)
			{
				free(p_cpy);
				return (existing_path);
			}
			else
			{
				free(cmd_path);
				dir = strtok(NULL, ":");
			}
		}
		free(p_cpy);
		if (stat(cmd, &buf) == 0)
		{
			return (cmd);
		}
		return (NULL);
	}
	return (NULL);
}

/**
 * construct_cmd_path - construct the cmd path given dir and command
 * @dir: base directory
 * @cmd: input command
 *
 * Return: NULL if not exists or string containing the path
 */
char *construct_cmd_path(char *dir, char *cmd)
{
	char *cmd_path;
	int dir_len, cmd_len;

	cmd_len = _strlen(cmd);
	dir_len = _strlen(dir);
	cmd_path = malloc(cmd_len + dir_len + 2);
	if (cmd_path == NULL)
	{
		perror("Error Memory Allocation");
		exit(EXIT_FAILURE);
	}
	strcpy(cmd_path, dir);
	strcat(cmd_path, "/");
	strcat(cmd_path, cmd);
	strcat(cmd_path, "\0");

	return (cmd_path);
}

/**
 * does_path_exists - check if a constucted path exists
 * @path: input path to check
 *
 * Return: NULL if not exists or path itself
 */
char *does_path_exists(char *path)
{
	struct stat buf;

	if (stat(path, &buf) == 0)
	{
		return (path);
	}
	return (NULL);
}
