#include "shell.h"
/**
 * _Alias - works as man alias
 * @data: storage struct
 * Return: 0
 *
 */
int _Alias(data_t *data)
{
	int i = 0;
	char *ptr = NULL;
	list_t *nd = NULL;

	if (data->ac == 1)
	{
		nd = data->alias;
		while (nd)
		{
			printAlias(nd);
			nd = nd->nxt;
		}
		return (0);
	}
	for (i = 1; data->av[i]; i++)
	{
		ptr = str_chr(data->av[i], '=');
		if (ptr)
			setAlias(data, data->av[i]);
		else
			printAlias(nd_start(data->alias, data->av[i], '='));
	}
	return (0);
}
