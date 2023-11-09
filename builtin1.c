#include "shell.h"

/**
 * myhistory - Display the command history list with line numbers.
 * @info: Structure containing potential arguements, used to maintain a consistent function prototype.
 * Return: Always 0.
 */

int myhistory(info_t *info)
{
	print_history(info->history);
	return 0;
}

/**
 * unsetAlias- Unset an alias by name.
 * @info: parameter struct.
 * @name: The name of the alias to unset.
 * Return: Always 0 on success 1 on error
 */
int unsetAlias(info_t *info, char *name)
{
	char *equal_sign, saved_char;
	int ret;

	equal_sign = _strchr(name, '=');
	if (!equal_sign)
		return 1;
	saved_char = *equal_sign;
	*equal_sign = '\0';
	ret = deleteAlias(&(info->alias),
		getAliasIndex(info->alias, aliasStartsWith(info->alias, name, -1)));
	*equal_sign = saved_char;
	return ret;
}
/**
 * setAlias - Set an alias to string.
 * @info: parameter struct
 * @str: The alias string in the format "name=value".
 * Return: 0 on success, 1 on error
 */
int setAlias(info_t *info, char *str)
{
	char *equal_sign;

	equal_sign = _strchr(str, '=');
	if (!equal_sign)
		return 1;
	if (!*++equal_sign)
		return unsetAlias(info, str);
	unsetAlias(info, str);
	return (addAliasEnd(&(info->alias), str, 0) == NULL);
}
/**
 * printAlias - Print an alias string.
 * @aliasNode: The alias node.
 * Return: 0 on success 1 on error
 */
int printAlias(list_t *aliasNode)
{
	char *equal_sign, *aliasName;
	
	if (aliasNode)
	{
		equal_sign = _strchr(aliasNode->str, '=');
		for (aliasName = aliasNode->str; aliasName <= equal_sign; aliasName++)
			_putchar(*aliasName);
		_putchar('\'');
		_puts(equal_sign + 1);
		_puts("'\n");
		return (0);
	}
	return 1;
}
/**
 * myalias - Mimics the alias built-in (man alias).
 * @info: Structure containing potential arguements, used to maintain constant function prototype.
 * Return: Always 0
 */
int myalias(info_t *info)
{
	int i;
	char *equal_sign;
	list_t *aliasNode;

	if (info->argc == 1)
	{
		aliasNode = info->alias;
		while (aliasNode)
		{
			printAlias(aliasNode);
			aliasNode = aliasNode->next;
		}
		return 0;
	}
	for (i = 1; info->argv[i]; i++)
	{
		equal_sign = _strchr(info->argv[i], '=');
		if (equal_sign)
			setAlias(info, info->argv[i]);
		else
			printAlias(aliasStartsWith(info->alias, info->argv[i], '='));
	}
	return (0);
}

