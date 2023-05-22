#include "main.h"

/**
 * _input_buf - buffer chained commands
 * @info: parameter struct
 * @buf: address of the buffer
 * @len: address of length variable
 * Return: the bytes read
 */

ssize_t _input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t d = 0;
	size_t len_g = 0;

	if (!*len) /*if nothing is left in the uffer fill it again*/
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		d = getline(buf, &len_g, stdin);
#else
	   	d = _getline(info, buf, &len_g);
#endif
	    if (d > 0)
		{
			if ((*buf)[d - 1] == '\n')
			{
				(*buf)[d - 1] = '\0'; /*removes trailling newline*/
				r--;
			}
			info->linecount_flag = 1;
			remove_coments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = d;
				info->cmd_buf = buf;
			}
		}
	}
	return (d);
}

/**
 * _getinput - gets a line minus the newline
 * @info - parameter struct
 * Return: byte read
 */
 ssize_t _getinput(info_t *info)
 {
 	static char *buf;
 	static size_t i, j, len;
 	ssize_t d = 0;
 	char **buf_g = &(info->arg), *g;

 	_putchar(BUF_FLUSH);
 	d = _input_buf(info, &buf, &len);
 	if (d == -1) /*EOF*/
 		return (-1);
 	if (len)
	 {
	 	j = i; /*init new iterator to the current buf position */
	 	g = buf + i;/*gets pointer for return*/

	 	check_chain(info, buf, &j, i, len);
	 	while(j < len)
		 {
		 	if (is_chain(info, buf, &j))
		 		break;
		 	j++;
		 }

		 i = j + 1;
		 if (i >= len)
		 {
		 	i = len = 0; /*reset position and length*/
		 	info->cmd_buf_type = CMD_NORM;
		 }

		 *buf_g = g;
		 return (_strlen(g));
	 }

	 *buf_g = buf;
	 return (r);
 }

 /**
  * read_buf - read a buffer
  * @info: parameter struct
  * @buf: buffer
  * @i: size
  * Return: d
  */
 ssize_t read_buf(info_t *info, char *buf, size_t *i)
 {
 	ssize_t d = 0;

 	if (*i)
 		return (0);
 	d = read(info->readfd, buf, READ_BUF_SIZE);
 	if (d >= 0)
 		*i = d;
 	return (d);
 }

 /**
  * _getline - gets the next line of input from standard inputs
  * @info: paraeter struct
  * @ptr: address of pointer to buffer, preallocated or NULL
  * @length: size of preallocated pointer buffer if not NULL
  * return: sd;
  */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t j;
	ssize_t d = 0, s = 0;
	char *g = NULL, *new_g = NULL, *C;

	g = *ptr;
	if (g && length)
		s = *length;
	if (i == len)
		i = len = 0;

	d = read_buf(info, buf, &len);
	if (d == -1 || (d == 0 && len == 0))
		return (-1);

	C = _strchr(buf + i, '\n');
	j = C ? 1 + (unsigned int)(C - buf) : len;
	new_g = realloc(g, s, s ? s + j : j + 1);
	if (!new_g)
		return (g ? free(g), -1 : -1);

	if (s)
		_strncat(new_g, buf + i, k - i);
	else
	{
		_strncpy(new_g, buf + i, k - i + 1);
	}
	s = s + k - i;
	i = j;
	g = new_g;

	if (length)
		*length = s
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
