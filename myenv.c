#include "shell.h"

/**
 * _myenv - prints our current working environment
 * @info: contain arguments used in maintaining the
 * function prototype
 * Return: 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - print environment variable value
 * @info: contain arguments used in maintaining the
 * function prototype
 * @name: variable name
 *
 * Return: variable value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *z;

	while (node)
	{
		z = starts_with(node->str, name);
		if (z && *z)
			return (z);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - sets or modify environment varaible
 * @info:  contain arguments used in maintaining the
 * function prototype
 *  Return: 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - unset environment variable
 * @info:  contain arguments used in maintaining the
 * function prototype
 * Return: 0
 */
int _myunsetenv(info_t *info)
{
	int x;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (x = 1; x <= info->argc; x++)
		_unsetenv(info, info->argv[x]);

	return (0);
}

/**
 * populate_env_list - print environment list
 * @info:  contain arguments used in maintaining the
 * function prototype
 * Return: 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t x;

	for (x = 0; environ[x]; x++)
		add_node_end(&node, environ[x], 0);
	info->env = node;
	return (0);
}
