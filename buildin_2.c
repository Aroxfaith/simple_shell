#include "shell.h"

/**
 * _myhistory - shows history list by one command line,followed
 * by line numbers from 0.
 * @info: contain arguments used in maintaining the
 * function prototype.
 * Return: 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - ungenerate string alias
 * @info: parameter struct
 * @str: string alias
 *
 * Return: 0 on success else 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *z, y;
	int ref;

	z = _strchr(str, '=');
	if (!z)
		return (1);
	y = *z;
	*z = 0;
	ref = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*z = y;
	return (ref);
}

/**
 * set_alias - generate string alias
 * @info: parameter struct
 * @str: string alias
 *
 * Return: 0 on success else 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *z;

	z = _strchr(str, '=');
	if (!z)
		return (1);
	if (!*++z)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints out string alias
 * @node: node
 * Return: 0 on success else 1 on error
 */
int print_alias(list_t *node)
{
	char *z = NULL, *a = NULL;

	if (node)
	{
		z = _strchr(node->str, '=');
		for (a = node->str; a <= z; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(z + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - generate alias that looks like builtin ones
 * @info:  contain arguments used in maintaining the
 *      function prototype.
 *  Return: 0
 */
int _myalias(info_t *info)
{
	int x = 0;
	char *z = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
		{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (x = 1; info->argv[x]; x++)
	{
		z = _strchr(info->argv[x], '=');
		if (z)
			set_alias(info, info->argv[x]);
		else
			print_alias(node_starts_with(info->alias, info->argv[x], '='));
	}

	return (0);
}
