#include "main.h"

/**
 * *_strncpy - copies a string
 * @dest: the destination string to be copied to
 * @src: the source string
 * @n: the amount of characters toe copied
 * Return: the string concatinated
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *d = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (d);
}

/**
 * *_strncat - concatenates two strings
 * @dest: first string
 * @src: second string
 * @n: the maximum amount of bytes to be used
 * Return: the joined string
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *d = dest;

	int i = 0;
	int j = 0;

	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++
	}
	if (j < n)
		dest[i] =  '\0';
	return (d);
}

/**
 * strchr - locates a character in a string
 * @s: the string to be parsed
 * @c: the character to look for
 * Return: s-a pointer to the memory area s
 */
char *strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
