#include "shell.h"
/**
 * _help - helper function
 * @data: storage struct
 * Return: 0;
 *
 */
int _help(data_t *data)
{
	char **x;

	x = data->av;
	puts_("help call works out, Func not yet implemented \n");
	if (0)
		puts_(*x);
	return (0);
}
