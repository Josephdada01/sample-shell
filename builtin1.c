#include "shell.h"

/**
 * display_history - a function that display history
 * @info: structure containing potential arguments
 * Return: the history
 */
int display_history(info_t, *info)
{
	print_list(info->history);
	return (0);
}
/**
 * unset_alias - a function that unset the alias
 * @str: a pointer
 * @info: structure containing potential arguments
 * Return: 0 always
 */
int unset_alias(info_t *info, char *str)
{
	char *equals_sign, temp;
	int ret;

	equals_sign = strchr(str, '=');
	if (!equals_sign)
	{
		return (1);
	}
	temp = *equals_sign;
	*equal_signs = '\0';

	ret = delete_alias(&(info->alias), str);
	*equals_sign = temp;
	return (ret);
}
/**
 * set_alias - a function that set alias
 * @info: a structure containing potential arguments
 * @str: a pointer
 * Return: 0 always
 */
int set_alias(info_t *info, char *str)
{
	char *equals_sign;

	equals_sign = strchr(str, '=');
	if (!equals_sign)
	{
		return (1);
	}
	if (!*++equals_sign)
	{
		return (unset_alias(info, str);
	}
	unset_alias(info, str);
	return (add_alias(&(info->alias), str) == NULL):
}
/**
 * int
