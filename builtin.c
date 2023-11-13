#include "custom_shell.h"

/**
 * exitShell - exit the custom shell
 * @info: Structure containing potential arguments, used to maintain
 *         a consistent function prototype.
 * Return: Exits with a given exit status, (0) if info->argv[0] != "exit"
 */
int exitShell(info_t *info)
{
	int exitStatus;

	if (info->argv[1])  /* If there is an exit argument */
	{
		exitStatus = _erratoi(info->argv[1]);
		if (exitStatus == -1)
		{
			info->status = 2;
			printError(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * changeDirectory - change the current directory of the process
 * @info: Structure containing potential arguments, used to maintain
 *         a consistent function prototype.
 * Return: Always 0
 */
int changeDirectory(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdirRet;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdirRet = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdirRet = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdirRet = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdirRet = chdir(info->argv[1]);
	if (chdirRet == -1)
	{
		printError(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * displayHelp - display help information for the custom shell
 * @info: Structure containing potential arguments, used to maintain
 *         a consistent function prototype.
 * Return: Always 0
 */
int displayHelp(info_t *info)
{
	char **argArray;

	argArray = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argArray); /* temp att_unused workaround */
	return (0);
}

