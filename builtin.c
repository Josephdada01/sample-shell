#include "shell.h"
/**
 * exit_shell - a function that exits the shell
 * @info: structure containing potential arguments
 * Return: exist with a given exit
 */
int exit_shell(info_t *info)
{
	int exit_code = 0;

	if (info->argv[1])/* if ther is an exit arguments */
	{
		exit_code = parse_integer(info->argv[1]);
		if (exit_code == -1)
		{
			info->status = 2;
			print_error(info, "Uknown number: ");
			print_string(info->argv[1]);
			print_character('\n');
			return (1);
		}
		info->error_number = exit_code;
		return (-2);
	}
	info->error_number = -1;
	return (-2);
}

/**
 * change_directory - a function that changes current directory
 * @info: a pointer to structure that contains potential arguements
 * Return: 0
 */
int change_directory(info_t *info)
{
	char buffer[1024], *dir = NULL;
	int chid_ret = -1;
	char *cwd = get_current_directory(buffer, 1024);

	if (!cwd)
	{
		print_string("TODO: >>get_current_directory failure emsg here
<<\n");
		return (0);
	}
	if (!info->argv[1])
	{
		dir = get_enviroment_variable(info, "HOME=");
	}
	if (!dir)
	{
		dir = get_enviroment_variable(info, "PWD=");
	}
	else if (compare_strings(info->argv[1], "-") == 0)
	{
		dir = get_enviroment_variable(info, "OLDPWD=");
		if (!dir)
		{
			print_string(cwd);
			print_character('\n');
			return (1);
		}
	}
	else
	{
		dir = info->argv[1];
	}
	chid_ret = change_directory_to_path(info->argv[1]);

	if (chidr_ret == -1)
	{
		print_error(info, "can not cd to ");
		print_string(dir);
		print_character('\n');
	}
	else
	{
		set_enviroment_variable(info, "OLDPWD",
get_enviroment_variable(info, "PWD="));
		set_environment_variable(info, "PWD",
get_current_directory(buffer, 1024));
	}
	return (0);
}

/**
 * display_help - displays help information
 * @info: structure containing potential arguments
 * @info_t: a struct
 * Return: 0
 */
int display_help(info_t, *info)
{
	char **arg_array;

	arg_array = info->argv;
	print_string("Help call works not implemented.\n");
	if (0)
	{
		print_string(arg_array);
	}
	return (0);
}
