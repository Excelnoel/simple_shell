#include "shell.h"

/**
 * printEmvironment - Prints the current environment
 * @info: Structure containing potential arguments. 
 * Return: Always 0
 */
int printEnvironment(info_t *info)
{
	printEnvironment(info->env);
	return 0;
}

/**
 * getEnvironmentVariable - Gets the value of an environment variable.
 * @info: Structure containing potential arguments. 
 * @name: Environment variable name
 * Return: the value of the variable or NULL if not found.
 */
char *getEnvironmentVariable(info_t *info, const char *name)
{
	list_t *currentNode = info->env;
	char *variableValue;

	while (currentNode)
	{
		variableValue = startsWith(currentNode->str, name);
		if (variableValue && *variableValue)
			return variableValue;
		currentNode = currentNode->next;
	}
	return NULL;
}

/**
 * setEnvironmentVariable - Initialize a new environment variable or modify an existing one
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int setEnvironmentVariable(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return 1;
	}
	if (setEnvironment(info, info->argv[1], info->argv[2]))
		return 0;
	return 1;
}

/**
 * unsetEnvironmentVariable - Remove an environment variable
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int unsetEnvironmentVariable(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unsetEnvironment(info, info->argv[i]);

	return 0;
}

/**
 * initializeEnvironmentList - Populates the environment linked list
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int initializeEnvironmentList(info_t *info)
{
	list_t *currentNode = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		addNodeToEnd(&currentNode, environ[i], 0);
	info->env = currentNode;
	return 0;
}

