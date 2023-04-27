#include "shell.h"

/**
 * input_buf - buffer command chains
 * @info: parameter struct
 * @buf: address to the buf
 * @len: address to len
 * Return: size of byte
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t s = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		s = getline(buf, &len_p, stdin);
#else
		s = _getline(info, buf, &len_p);
#endif
		if (s > 0)
		{
			if ((*buf)[s - 1] == '\n')
			{
				(*buf)[s - 1] = '\0';
				s--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);

			{
				*len = s;
				info->cmd_buf = buf;
			}
		}
	}
	return (s);
}

/**
 * get_input - gets input
 * @info: parameter struct
 *
 * Return: size of byte
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t x, y, len;
	ssize_t s = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	s = input_buf(info, &buf, &len);
	if (s == -1) /* EOF */
		return (-1);
	if (len)
	{
		y = x;
		p = buf + x;

		check_chain(info, buf, &y, x, len);
		while (y < len)
		{
			if (is_chain(info, buf, &y))
				break;
			y++;
		}

		x = y + 1;
		if (x >= len)
		{
			x = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
		}

	*buf_p = buf;
	return (s);
}

/**
 * read_buf - read buffer
 * @info: parameter struct
 * @buf: buf
 * @i: size
 *
 * Return: s
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t s = 0;

	if (*i)
		return (0);
	s = read(info->readfd, buf, READ_BUF_SIZE);
	if (s >= 0)
		*i = s;
	return (s);
}

/**
 * _getline - it gets new line from STDIN
 * @info: parameter struct
 * @ptr: address to pointer
 * @length: length of ptr
 *
 * Return: s
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t x, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *z = NULL, *new_p = NULL, *c;

	z = *ptr;
	if (z && length)
		s = *length;
	if (x == len)
		x = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + x, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(z, s, s ? s + k : k + 1);
	if (!new_p)
		return (z ? free(z), -1 : -1);
	if (s)
		_strncat(new_p, buf + x, k - x);
	else
		_strncpy(new_p, buf + x, k - x + 1);

	s += k - x;
	x = k;
	z = new_p;

	if (length)
		*length = s;
	*ptr = z;
	return (s);
}

/**
 * sigintHandler - Handler
 * @sig_num: number of signal
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
