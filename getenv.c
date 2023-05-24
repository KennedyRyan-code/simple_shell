#include "main.h"

/**
 * get__environ - return the string array copy of our envieon
 * @info: structure containing potential arguments
 * Return: 0
 */
char **get__environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strs(info->env);
		info->env_changed = 0;
	}
	return (info->environ);

}

/**
 * unset_env - remove an environment variable
 * @info: structure containing potential arguments.
 * @var: the string env variable property
 * Return: 1 0n delete, else 0
 */
int unset_env(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *d;

	if (!node || !var)
		return (0);

	while (node)
	{
		d = starts_with(node->str, var);
		if (d && *d == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * set_env - initialize a new environment variable/modify
 * @info: structure containg potential arguments.
 * @var: the string env variable proberty
 * Return: 0
 */
int set_env(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *d;

	if (!var || !value)
		return (0);

	buf = malloc(str_len(var) + str_len(value) + 2);
	if (!buf)
		return (1);
	str_cpy(buf, var);
	str_cat(buf, "=");
	str_cat(buf, value);
	node = info->env;
	while (node)
	{
		d = starts_with(node->str, var);
		if (d && *d == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
