#include "shell.h"
/**
 * clearInfo - Initialize the info_t struct
 * @info: Pointer to the info_t struct
 */
void clear_Info(info_t *info)
{
	info->argument = NULL;
	info->argumentVector = NULL;
	info->path = NULL;
	info->argument = 0;
}
/**
 * setInfo - Initialize the info_t struct
 * @info: Pointer to the info_t structstruct address
 * @arguments: Arguement vector
 */
void setInfo(info_t *info, char **arguments)
{
	int i = 0;

	info->filename = arguments[0];
	
	if (info->argument)
	{
		info->argumentVector = splitString(info->argument, " \t");
		if (!info->argumentVector)
		{
			info->argumentVector = malloc(sizeof(char *) * 2);
			if (info->argumentVector)
			{
				info->argument[0] = duplicateString((info->argument);
				info->argumentVector[1] = NULL;
			}
		}
		for (i = 0; info->argumentvector && info->argv[i]; i++)
			;
		info->argumentCount = i;

		replaceAliases(info);
		replaceVariables(info);
	}
}
/**
 * freeInfo - free the fields of the info_t struct
 * @info: Pointer to the info_t struct 
 * @freeAll: True if freeing all fields
 */
void freeInfo(info_t *info, int freeAll)
{
	free(info->argumentVector);
	info->argumentVector = NULL;
	info->path = NULL;

	if (freeAll)
	{
		if (!info->commandBuffer)
			free(info->argument);

		if (info->environment)
			freeList(&(info->env));

		if (info->commandHistory)
		
			freeList(&(info->history));
		if (info->aliasList)
			freeList(&(info->aliasList));
		free(info->environmentVariables);
		info->environmentvariables = NULL;
		batchFree((void **)info->commandBuffer);
		if (info->readFileDescriptor > 2)
			close(info->readFileDescriptor);
		outputCharacter(BUFFER_FLUSH);
	}
}
