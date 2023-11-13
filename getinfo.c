#include "shell.h"

/**
 * clearInfo - Initialize the info_t struct
 * @info: Pointer to the info_t struct
 */
void clearInfo(info_t *info)
{
    info->argument = NULL;
    info->argumentVector = NULL;
    info->path = NULL;
    info->argc = 0;  // Change 'argument' to 'argc'
}

/**
 * setInfo - Initialize the info_t struct
 * @info: Pointer to the info_t structstruct address
 * @arguments: Argument vector
 */
void setInfo(info_t *info, char **arguments)
{
    int i = 0;

    info->fname = arguments[0];  // Change 'filename' to 'fname'

    if (info->argument)
    {
        info->argumentVector = tokenizeString(info->argument, " \t");  // Change 'splitString' to 'tokenizeString'
        if (!info->argumentVector)
        {
            info->argumentVector = malloc(sizeof(char *) * 2);
            if (info->argumentVector)
            {
                info->argumentVector[0] = duplicateString(info->argument);  // Change '(info->argument)' to 'info->argument'
                info->argumentVector[1] = NULL;
            }
        }
        for (i = 0; info->argumentVector && info->argumentVector[i]; i++)  // Change 'info->argv' to 'info->argumentVector'
            ;
        info->argc = i;  // Change 'argumentCount' to 'argc'

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
        info->environmentVariables = NULL;

        batchFree((void **)info->commandBuffer);
        
        if (info->readfd > 2)  // Change 'readFileDescriptor' to 'readfd'
            close(info->readfd);

        _eputchar(BUF_FLUSH);  // Change 'outputCharacter' to '_eputchar' and 'BUFFER_FLUSH' to 'BUF_FLUSH'
    }
}

