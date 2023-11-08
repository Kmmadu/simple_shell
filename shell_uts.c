#include "shell.h"
#include <stdio.h>

/**
 * check_interactive - Check if the shell is running in interactive mode.
 * @info: Pointer to the shell's info structure.
 *
 * Return: 1 if in interactive mode, 0 otherwise.
 */
int check_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

int main(void)
{
printf("Hello from shell_uts!\n");
return (0);
}


/**
 * is_delimiter - Check if a character is a delimiter.
 * @c: The character to check.
 * @delim: The delimiter string.
 * Return: 1 if true, 0 if false.
 */
int is_delimiter(char c, char *delim)
{
	while (*delim)
	{
		if (*delim == c)
			return (1);
		delim++;
	}
	return (0);
}

/**
 * is_alpha - Check if a character is alphabetic.
 * @c: The character to check.
 * Return: 1 if 'c' is alphabetic, 0 otherwise.
 */
int is_alpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * custom_atoi - Convert a string to an integer.
 * @s: The string to be converted.
 * Return: 0 if no numbers in the string, the converted number otherwise.
 */
int custom_atoi(char *s)
{
	int i = 0;
	int sign = 1;
	int output = 0;

	while (s[i] != '\0')
	{
		if (s[i] == '-' && i == 0)
		{
			sign = -1;
		}
		else if (s[i] >= '0' && s[i] <= '9')
		{
			output = output * 10 + (s[i] - '0');
		}
		else
		{
			break;  /* Exit the loop if a non-numeric character is encountered. */
		}
		i++;
	}

	return (output * sign);
}

