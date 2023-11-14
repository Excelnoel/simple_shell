#include "shell.h"

/**
 * isCommandExecutable - Checks if a file is an executable command
 * @info: The info struct (not used in this function)
 * @path: Path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
size_t _strlen(char *str);
char *_strcat(char *dest, char *src);

int isCommandExecutable(info_t *info, char *path)
{
    struct stat st;

    (void)info;
    if (!path || stat(path, &st))
        return 0;

    if (S_ISREG(st.st_mode))
    {
        return 1;
    }
    return 0;
}

/**
 * duplicateCharacters - Duplicates characters within a specified range
 * @pathStr: The PATH string
 * @start: Starting index
 * @stop: Stopping index
 *
 * Return: Pointer to the new buffer
 */
char *duplicateCharacters(char *pathStr, int start, int stop)
{
    static char buffer[1024];
    int i = 0, k = 0;

    for (k = 0, i = start; i < stop; i++)
        if (pathStr[i] != ':')
            buffer[k++] = pathStr[i];
    buffer[k] = '\0';
    return buffer;
}

/**
 * findCommandPath - Finds the specified command in the PATH string
 * @info: The info struct (not used in this function)
 * @pathStr: The PATH string
 * @cmd: The command to find
 *
 * Return: Full path of cmd if found, or NULL
 */
char *findCommandPath(info_t *info, char *pathStr, char *cmd)
{
    int i = 0, currPos = 0;
    char *path;

    if (!pathStr)
        return NULL;

    if ((_strlen(cmd) > 2) && startsWith(cmd, "./"))
    {
        if (isCommandExecutable(info, cmd))
            return cmd;
    }

    while (1)
    {
        if (!pathStr[i] || pathStr[i] == ':')
        {
            path = duplicateCharacters(pathStr, currPos, i);
            if (!*path)
                _strcat(path, cmd);
            else
            {
                _strcat(path, "/");
                _strcat(path, cmd);
            }
            if (isCommandExecutable(info, path))
                return path;

            if (!pathStr[i])
                break;

            currPos = i;
        }
        i++;
    }

    return NULL;
}

