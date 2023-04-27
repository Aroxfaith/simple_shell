#include "shell.h"

/**
 * get_environ - get string array of our environment
 * @info: contain argument used in maintaining the
 * fuction prototype
 * Return: 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - unset environment variable
 * @info:  contain argument used in maintaining the
 * fuction prototype
 * @var: environment variable
 * Return: 1 if delete else 0
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t x = 0;
	char *z;

	if (!node || !var)
		return (0);

	while (node)
	{
		z = starts_with(node->str, var);
		if (z && *z == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), x);
			x = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		x++;
	}
	return (info->env_changed);
}

/**
 * _setenv - sets or modify environment variable
 * @info: contain arguments used in maintaining the
 * function prototype
 * @var: environment variable
 * @value: environment variable value
 * Return: 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *z;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		z = starts_with(node->str, var);
		if (z && *z == '=')
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
