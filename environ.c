#include "main.h"

/**
 * _ourenv - prints the current environmet
 * @info: structure containing potential argument
       (used to maintain constant fuction prototye)
 * Return: 0
 */
int _ourenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info: structure containing potential arguments.
 * @name: env variable name.
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *d;

	while (node)
	{
		d = start_with(node->str, name);
		if (d && *d)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 *_oursetenv -initialise new environent variable/modify existing environment
 * @info: structure containing potential argument
 *used to maintain constant fuction prototye)
 * Return: 0
 */
int _oursetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("incorrect no of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _ourunsetenv - remove an environment variable
 *@info: structure containing potential argument
 *(used to maintain constant fuction prototye)
 *Return: 0;
 */
int _ourunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("few arguments\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);
	return (0);
}

/**
 * populateenv_list - populates env linked list
 * @info: structure containing potential argument
 *(maintain constant function prototye)
 *Ruturn: 0;
 */
int populateenv_list(info_t *info)
{
	list_t *node -= NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
