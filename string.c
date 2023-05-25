#include "main.h"

/**
 * str_len - returns the length of a string
 * @str: the string
 *
 * Return: len
 */

size_t str_len(const char *str)
{
	size_t len = 0;

	while (*str != '\0')
	{
		len++;
		str++;
	}

	return (len);
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
	size_t i, l = 0;

	i = str_len(dest);

	for (l = 0; src[l] != '\0'; l++)
	{
		dest[i + l] = src[l];
	}
	dest[l + l] = '\0';

	return (dest);
}


/**
 * str_cpy - copy the string
 * @dest: char to check
 * @src: char to check
 * Return: a pointer
 */

char *str_cpy(char *dest, char *src)
{
	size_t a;

	for (a = 0; src[a] != '\0'; a++)
		dest[a] = src[a];

	dest[a] = '\0';

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
int str_cmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	return (*s1 - *s2);
}
