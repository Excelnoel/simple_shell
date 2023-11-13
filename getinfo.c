#include "shell.h"

/**
 * clearInfo - Initialize the info_t struct
 * @info: Pointer to the info_t struct
 */
void clearInfo(info_t *info)
{
    info->arg = NULL;
    info->argv = NULL;
    info->path = NULL;
    info->argc = 0;  // Change 'argument' to 'argc'
}

/**
 * setInfo - Initialize the info_t struct
 * @info: Pointer to the info_t struct
 * @arguments: Argument vector
 */
void setInfo(info_t *info, char **arguments)
{
    int i = 0;

    info->fname = arguments[0];  // Change 'filename' to 'fname'

    if (info->arg)
    {
        info->argv = replaceString(info->arg, " \t");  // Change 'splitString' to 'tokenizeString'
        if (!info->argv)
        {
            info->argv = malloc(sizeof(char *) * 2);
            if (info->argv)
            {
                info->argv[0] = duplicateString(info->arg);  // Change '(info->argument)' to 'info->argument'
                info->argv[1] = NULL;
            }
        }
        for (i = 0; info->argv && info->argv[i]; i++)  // Change 'info->argv' to 'info->argumentVector'
            ;
        info->argc = i;  // Change 'argumentCount' to 'argc'

        replaceAliases(info);
        replaceVariables(info);
    }
}

/**
 * freeInfo - Free the fields of the info_t struct
 * @info: Pointer to the info_t struct
 * @freeAll: True if freeing all fields
 */
void freeInfo(info_t *info, int freeAll)
{
    freeMemoryTripple((void ***)info->argv);
    info->argv = NULL;
    info->path = NULL;

    if (freeAll)
    {
        if (!info->cmd_buf)
            free(info->arg);

        if (info->env)
            freeList(&(info->env));

        if (info->history)
            freeList(&(info->history));

        if (info->alias)
            freeList(&(info->alias));

        freeMemoryTripple((void ***)info->environ);
        info->environ= NULL;

        freeMemoryTripple((void ***)info->cmd_buf);

        if (info->readfd > 2)  // Change 'readFileDescriptor' to 'readfd'
            close(info->readfd);

        _eputchar(BUF_FLUSH);  // Change 'outputCharacter' to '_eputchar' and 'BUFFER_FLUSH' to 'BUF_FLUSH'
    }
}

