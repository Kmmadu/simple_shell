#include "shell.h"

/**
 * unset_alias_by_name - Unsets an alias by its name.
 * @info: Structure containing potential arguments.
 * @alias_name: The name of the alias to unset.
 *
 * This function unsets an alias identified by its name.
 * in the alias list, and if found, removes it from the list.
 *
 * Return: 0 on success, 1 on error.
 */
int unset_alias_by_name(info_t *info, char *alias_name)
{
	char *equal_sign, tmp_char;
	int result = 1;

	equal_sign = _strchr(alias_name, '=');

	if (equal_sign)
	{
		tmp_char = *equal_sign;
		*equal_sign = '\0';

		list_t *alias_node = node_starts_with(info->alias, alias_name, -1);

		if (alias_node)
		{
			result = delete_node_at_index(&(info->alias), get_node_index(info->alias, alias_node));
		}

		*equal_sign = tmp_char;
	}

	return (result);
}

/**
 * add_alias - Add an alias to the list
 * @info: Parameter struct
 * @str: The alias string in the format "name=value"
 *
 * This function adds an alias identified
 * It checks if the input string is a valid
 *
 * Return: 0 on success, 1 on error.
 */
int add_alias(info_t *info, char *str)
{
	char *equal_sign, tmp_char;
	int result = 1;

	equal_sign = _strchr(str, '=');

	if (equal_sign)
	{
		tmp_char = *equal_sign;
		*equal_sign = '\0';

		result = unset_alias_by_name(info, str);

		*equal_sign = tmp_char;

		if (result == 0)
		{
			result = add_node_end(&(info->alias), str, 0) == NULL;
		}
	}

	return (result);
}

/**
 * display_history - Displays the command history, showing each command with
 *                   its line number, starting at 0.
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int display_history(info_t *info)
{
	int line_number = 0;
	list_t *node = info->history;

	for (line_number = 0; node; node = node->next, line_number++)
		printf("%d %s\n", line_number, node->str);

	return (0);
}

/**
 * handle_alias - Handle alias commands,
 * @info: Structure containing potential arguments.
 *
 * This function handles alias commands.
 * if called without arguments,
 * or prints the corresponding
 * not in 'name=value' format.
 *
 * Return: Always 0.
 */
int handle_alias(info_t *info)
{
	int i = 0;

	if (info->argc == 1)
	{
		list_t *node = info->alias;

		while (node)
		{
			print_alias_entry(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		char *p = _strchr(info->argv[i], '=');

		if (p)
			set_alias_entry(info, info->argv[i]);
		else
			print_alias_entry(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}

/**
 * print_alias_entry - Print an alias name and its value.
 * @node: The alias node to be printed.
 *
 * This function prints the name and value of the provided alias node.
 *
 * Return: 0 on success, 1 on error
 */
int print_alias_entry(list_t *node)
{
	if (node)
	{
		char *equal_sign = _strchr(node->str, '=');

		if (equal_sign)
		{
			for (char *c = node->str; c < equal_sign; c++)
				_putchar(*c);

			_puts("'");
			_puts(equal_sign + 1);
			_puts("'\n");

			return (0);
		}
	}

	return (1);
}

