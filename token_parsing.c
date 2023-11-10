#include "shell.h"
#include <stdlib.h>

/**
 * is_delim - Check if a character is a delimiter.
 * @c: The character to check.
 * @delim: The string of delimiters.
 *
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */
int is_delim(char c, char *delim)
{
	while (*delim)
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

/**
 * customStringSplit - Split a string into words using a single delimiter.
 * @str: The input string to be split.
 * @d: The delimiter character.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **customStringSplit(char *str, char d)
{
	int idx, wIdx, cCnt, numwords = 0, cIdx;
	char **rArr;

	if (str == NULL || str[0] == '\0')
		return (NULL);

	for (idx = 0; str[idx] != '\0'; idx++)
	{
		if (str[idx] != d && (str[idx + 1] == d || str[idx + 1] == '\0'))
			numwords++;
	}

	if (numwords == 0)
		return (NULL);
	rArr = malloc((numwords + 1) * sizeof(char *));
	if (!rArr)
		return (NULL);
	for (idx = 0, wIdx = 0; wIdx < numwords; wIdx++)
	{
		while (str[idx] == d)
			idx++;
		cCnt = 0;
		while (str[idx + cCnt] != d && str[idx + cCnt] != '\0')
			cCnt++;
		rArr[wIdx] = malloc((cCnt + 1) * sizeof(char));
		if (!rArr[wIdx])
		{
			for (cIdx = 0; cIdx < wIdx; cIdx++)
				free(rArr[cIdx]);
			free(rArr);
			return (NULL);
		}

		for (cIdx = 0; cIdx < cCnt; cIdx++)
			rArr[wIdx][cIdx] = str[idx++];
		rArr[wIdx][cCnt] = '\0';
	}
	rArr[numwords] = NULL;
	return (rArr);
}

/**
 * customStringSplitWithDelimiters - Split a string into
 * words using specified delimiters.
 * @str: The input string to be split.
 * @d: The delimiter string containing all possible delimiters.
 *
 * Return: A dynamically allocated array of strings, each representing a word
 *         from the input string. Returns NULL on failure or when no words are
 *         found.
 */
char **customStringSplitWithDelimiters(char *str, char *d)
{
	int numwords = 0, idx, cCnt, cIdx, wIdx;
	char **rArr;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	if (!d)
		d = " ";

	for (idx = 0; str[idx] != '\0';)
	{
		while (is_delim(str[idx], d))
			idx++;
		if (str[idx] != '\0')
			numwords++;
		while (str[idx] && !is_delim(str[idx], d))
			idx++;
	}
	if (numwords == 0)
		return (NULL);
	rArr = malloc((numwords + 1) * sizeof(char *));
	if (!rArr)
		return (NULL);
	for (idx = 0, wIdx = 0; wIdx < numwords; wIdx++)
	{
		while (is_delim(str[idx], d))
			idx++;
		for (cCnt = 0; str[idx + cCnt] && !is_delim(str[idx + cCnt], d); )
			cCnt++;
		rArr[wIdx] = malloc((cCnt + 1) * sizeof(char));
		if (!rArr[wIdx])
		{
			for (cIdx = 0; cIdx < wIdx; cIdx++)
				free(rArr[cIdx]);
			free(rArr);
			return (NULL);
		}
		strncpy(rArr[wIdx], str + idx, cCnt), rArr[wIdx][cCnt] = '\0', idx += cCnt;
	}
	rArr[numwords] = NULL;
	return (rArr);
}

