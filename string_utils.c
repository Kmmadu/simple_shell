#include "shell.h"

/**
 * _strdup - duplicate a string
 * @str: inputed string
 *
 * Return: pointer to the new string or NULL
 */
char *_strdup(char *str)
{
	int len, i;
	char *str_cpy;

	len = 0;
	if (str == NULL)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		len++;
	len++;
	str_cpy = malloc(len * sizeof(char));
	if (str_cpy == NULL)
		return (NULL);
	for (i = 0; i < len - 1; i++)
		str_cpy[i] = str[i];
	str_cpy[len - 1] = '\0';
	return (str_cpy);
}

/**
 * _max - determine the max between two integers
 * @n1: input integer
 * @n2: input integer
 *
 * Return: return the max between n1 and n2
 */
int _max(int n1, int n2)
{
	if (n1 > n2)
		return (n1);
	else
		return (n2);
}


/**
 * _strcmp - compare two strings
 * @str1: input string
 * @str2: input string
 *
 * Return: 0 if equals, and len(str1) - len(str2) if not
 */
int _strcmp(char *str1, char *str2)
{
	int len1, len2, max, i;

	len1 = _strlen(str1);
	len2 = _strlen(str2);
	max = _max(len1, len2);

	for (i = 0; i < max; i++)
	{
		if (str1[i] == str2[i])
			continue;
		else
			return (str1[i] - str2[i]);
	}
	return (0);
}
