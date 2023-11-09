#include "shell.h"

/**
 * is_delimiter - Check if a character is a delimiter.
 * @c: The character to check.
 * @delimiters: The string of delimiters.
 *
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */
int is_delimiter(char c, const char *delimiters)
{
while (*delimiters)
{
if (c == *delimiters)
return (1);
delimiters++;
}
return (0);
}

/**
 * count_words - Count the number of words in a string.
 * @str: The input string.
 * @delimiters: The string of delimiters.
 *
 * Return: The number of words.
 */
int count_words(const char *str, const char *delimiters)
{
int num_words = 0;
while (*str)
{
while (is_delimiter(*str, delimiters))
str++;
if (*str)
{
num_words++;
while (!is_delimiter(*str, delimiters) && *str)
str++;
}
}
return (num_words);
}

/**
 * split_string - Split a string into words using multiple delimiters.
 * @str: The input string to be split.
 * @delimiters: The delimiter string containing all possible delimiters.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **split_string(const char *str, const char *delimiters)
{
int num_words = count_words(str, delimiters);
if (num_words == 0)
return (NULL);
char **result = malloc((num_words + 1) * sizeof(char *));
if (!result)
return (NULL);
int i, j;
for (i = 0, j = 0; j < num_words; j++)
{
while (is_delimiter(str[i], delimiters))
i++;
int word_length = 0;
while (!is_delimiter(str[i + word_length], delimiters) && str[i + word_length])
word_length++;
result[j] = malloc((word_length + 1) * sizeof(char));
if (!result[j])
{
for (int k = 0; k < j; k++)
free(result[k]);
free(result);
return (NULL);
}
strncpy(result[j], str + i, word_length);
result[j][word_length] = '\0';
i += word_length;
}
result[j] = NULL;
return (result);
}

