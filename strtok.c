#include "main.h"

/**
 * **strtok - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: an array of strings, or NULL
 */

char **strtok(char *str, char *d)
{
	int j, k, i, m, num_words = 0;
	char **c;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			num_words++;

	if (num_words == 0)
	{
		return (NULL);
	}
	c = malloc((1 + num_words) * sizeof(char *));
	if (!c)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (is_delim(str[i], d))
			i++;
		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;
		c[j] = malloc((k + 1) * sizeof(char));
		if (!c[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(c);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			c[j][m] = str[i++];
		c[j][m] = 0;
	}
	c[j] = NULL;
	return (c);
}

/**
 * **strtok1 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtok1(char *str, char d)
{
	int m, k, j, i, num_words = 0;
	char **c;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			num_words++;
	if (num_words == 0)
	{
		return (NULL);
	}
	c = malloc((1 + num_words) * sizeof(char *));
	if (!c)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		c[j] = malloc((k + 1) * sizeof(char));
		if (!c[j])
		{
			for (k = 0; k < j; k++)
				free(c[k]);
			free(c);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			c[j][m] = str[i++];
		c[j][m] = 0;
	}
	c[j] = NULL;
	return (c);
}
