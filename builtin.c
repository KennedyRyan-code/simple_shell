#include "main.h"

/**
 * _ourhelp - changes the current directory of the process
 * @info: Structure containing potential arguments.
 *
 *  Return: Always 0
 */
int _ourhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}

/**
 * _ourexit - exits the shell
 * @info: Structure containing potential arguments.
 *
 * Return: exits with a given exit status.
 */

int _ourexit(info_t *info)
{
	int exitchecker;

	if (info->argv[1])
	{
		exitchecker = _erratoi(info->argv[1]);
		if (exitchecker == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _ourcd - changes the current directory of the process
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0
 */

int _ourcd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_result;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_result =
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_result = chdir(dir);
	}
	else if (str_cmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_result =
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_result = chdir(info->argv[1]);
	if (chdir_result == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _ourhistory - displays the history list, one command by line.
 * @info: Structure containing arguments.
 *
 *  Return: Always 0
 */
int _ourhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}
