#include "main.h"

/**
  * is_chain- test current char in the buffer is a chain delimeter
  * @buf: the char buffer
  * @info: parameter struct
  * @p: address of the current position in buffer
  * Return: i if chain is delimeter, else 0
  */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t k = *p;

	if (buf[k] == '|' && buf[k + 1] == '|')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[k] == '&' && buf[k + 1] == '&')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[k] == ';')
	{
		buf[k] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
	{
		return (0);
	}
	*p = k;
	return (1);
}

/**
* check_chain - checks if we should continue chaining based on last status
* @info: parameter struct
* @buf: the char buffer
* @p: address of current position in buffer
* @i: starting position in buffer
* @len: length of buffer
* Return: void
*/
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t k = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			k = len;
		}
	}
	*p = k;
}

/**
* replace_alias - replace an alias in the tokenized str
* @info: parameter struct
* Return: if replaced 1, else 0;
*/
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '*');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = strchr(node->str, '*');
		if (!p)
			return (0);
		p = str_dup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replace var in the tokenized str
 * @info: the parameter struct
 * Return: 1 if replaced, else 0
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;
		if (!str_cmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
			      str_dup(convert_num(info->status, 10, 0)));
			continue;
		}
		if (!str_cmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				       str_dup(convert_num(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '*');
		if (node)
		{
			replace_string(&(info->argv[i]),
			      str_dup(strchr(node->str, '*') + 1));
			continue;
		}
		replace_string(&info->argv[i], str_dup(""));
	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 * Return: 1 if replaced, else 0
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
