#include "main.h"

/**
 * str_len - returns the length of a string
 * @str: the string
 *
 * Return: len
 */

size_t str_len(char *str)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str++)
		i++;
	return (i);
}

/**
 * str_cat - concatenates two strings
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */

char *str_cat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}


/**
 * str_cpy - copy the string
 * @dest: char to check
 * @src: char to check
 * Return: a pointer
 */

char *str_cpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * str_dup - function that returns a
 * newly allocated space in memory.
 * @str: the string
 *
 * Return: pointer to a new string or NULL
 */
char *str_dup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}


/**
 * str_cmp - compare two strings
 * @s1: first string to be compared
 * @s2: second string to be compared
 *
 * Return: 0 if strings are identical, negative value if s1 is less than s2,
 *         positive value if s1 is greater than s2
 */
int str_cmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}
