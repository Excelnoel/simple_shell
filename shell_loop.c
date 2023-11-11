#include "shell.h"

/**
 * runShell - Main shell loop
 * @info: Pointer to the info_t struct for parameters and returns
 * @av: Argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int runShell(info_t *info, char **av)
{
	ssize_t readStatus = 0;
	int builtinResult = 0;

	while (readStatus != -1 && builtinResult != -2)
	{
		clearInfo(info);

		if (interactive(info))
			_puts("$ ");

		_eputchar(BUF_FLUSH);

		readStatus = getInput(info);

		if (readStatus != -1)
		{
			setInfo(info, av);
			builtinResult = findBuiltin(info);

			if (builtinResult == -1)
				findCommand(info);
		}
		else if (interactive(info))
			_putchar('\n');

		freeInfo(info, 0);
	}

	writeHistory(info);
	freeInfo(info, 1);

	if (!interactive(info) && info->status)
		exit(info->status);

	if (builtinResult == -2)
	{
		if (info->errNum == -1)
			exit(info->status);

		exit(info->errNum);
	}

	return (builtinResult);
}

/**
 * findBuiltin - Finds a builtin command
 * @info: Pointer to the info_t struct for parameters and returns
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int findBuiltin(info_t *info)
{
	int i, builtinResult = -1;

	builtinTable builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
	{
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->lineCount++;
			builtinResult = builtintbl[i].func(info);
			break;
		}
	}

	return (builtinResult);
}

/**
 * findCommand - Finds a command in PATH
 * @info: Pointer to the info_t struct for parameters and returns
 *
 * Return: void
 */
void findCommand(info_t *info)
{
	char *path = NULL;
	int i, count;

	info->path = info->argv[0];

	if (info->lineCountFlag == 1)
	{
		info->lineCount++;
		info->lineCountFlag = 0;
	}

	for (i = 0, count = 0; info->arg[i]; i++)
	{
		if (!isDelimiter(info->arg[i], " \t\n"))
			count++;
	}

	if (!count)
		return;

	path = findPath(info, _getenv(info, "PATH="), info->argv[0]);

	if (path)
	{
		info->path = path;
		forkCommand(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			 || info->argv[0][0] == '/') && isCommand(info, info->argv[0]))
			forkCommand(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			printError(info, "not found\n");
		}
	}
}

/**
 * forkCommand - Forks an exec thread to run a command
 * @info: Pointer to the info_t struct for parameters and returns
 *
 * Return: void
 */
void forkCommand(info_t *info)
{
	pid_t childPid;

	childPid = fork();

	if (childPid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}

	if (childPid == 0)
	{
		if (execve(info->path, info->argv, getEnviron(info)) == -1)
		{
			freeInfo(info, 1);

			if (errno == EACCES)
				exit(126);

			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));

		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);

			if (info->status == 126)
				printError(info, "Permission denied\n");
		}
	}
}

