#include "shell.h"

/**
 * _hsh - main loop
 * @data:struct
 * @argv:vector
 *
 * Return:value
 */

int _hsh(data_t *data, char **argv)
{
	ssize_t n = 0;
	int builtin = 0;

	while (n != -1 && builtin != -2)
	{
		clear_data(data);
		if (interactive_mode(data))
			puts_("$");
		eput_char(BUFFER_FLUSH);
		n = gets_load(data);
		if (n != -1)
		{
			set_data(data, argv);
			builtin = finds_builtin(data);
			if (builtin < 0)
				find_cmd(data);
		}
		else if (interactive_mode(data))
			put_char('\n');
		release_data(data, 0);
	}
	prints_hist(data);
	release_data(data, 1);
	if (!interactive_mode(data) && data->st)
		exit(data->st);
	if (builtin == -2)
	{
		if (data->num_error == -1)
			exit(data->st);
		exit(data->num_error);
	}
	return (builtin);
}
