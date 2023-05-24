#include "main.h"

/**
 * hsh- main shell loop
 * @info: the perameter and return information struct
 * @av: the argument vector from main.c
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t e = 0;
	int buildin_result = 0;

	while (e != -1 && buildin_result != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		e = _getinput(info);
		if (e != -1)
		{
			set_info(info, av);
			buildin_result = find_buildin(info);
			if (buildin_result == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (buildin_result == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (buildin_result);
}

/**
 * find_builtin - finds a buildin command
 * @info: the parameter & return info struct
 * Return: -1 if buildin not found, 0 on sucess
 * 1 if found but not successful
 * -2 if the buildin signals exit()
 */
int find_builtin(info_t *info)
{
	int i, _buildin_ret = -1;
	buildin_table buildintc1[] = {
	{"exit", _ourexit},
	{"env", _ourenv},
	{"help", _ourhelp},
	{"history", _ourhistory},
	{"setenv", _oursetenv},
	{"unsetenv", _ourunsetenv},
	{"cd", _ourcd},
	{"alias", _ouralias},
	{NULL, NULL},
	};

	for (i = 0; buildintc1[i].type; i++)
		if (str_cmp(info->argv[0], buildintc1[i].type) == 0)
		{
			info->line_count++;
			_buildin_ret = buildintc1[i].func(info);
			break;
		}
		return (_buildin_ret);
}

/**
 * find_cmd - find command in a PATH
 * @info: the parameter and return into struct
 * Return : void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, j;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++
		info->linecount_flag = 0;
	}
	for (i = 0, j = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			j++;
	if (!j)
		return;
	path = find_path(info, _getenv(info, "PATH"), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH")
		     || info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found \n");
		}
	}
}
/**
 * fork_cmd - forks an existing exec threaad to run the cmd
 * @info: parameter, info structure
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("error");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get__environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "permission denied\n");
		}
	}
}
