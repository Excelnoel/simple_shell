#include "shell.h"

/**
 * shellLoop - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shellLoop(info_t *info, char **av)
{
    ssize_t r = 0;
    int builtin_ret = 0;

    while (r != -1 && builtin_ret != -2)
    {
        clearInfo(info);
        if (interactive(info))
            _puts("$ ");
        _eputchar(BUF_FLUSH);
        r = getInput(info);
        if (r != -1)
        {
            setInfo(info, av);
            builtin_ret = findBuiltin(info);
            if (builtin_ret == -1)
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
    if (builtin_ret == -2)
    {
        if (info->err_num == -1)
            exit(info->status);
        exit(info->err_num);
    }
    return (builtin_ret);
}

/**
 * findBuiltin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         -2 if builtin signals exit()
 */
int findBuiltin(info_t *info)
{
    int i, built_in_ret = -1;
    builtin_table builtintbl[] = {
        {"exit", _myexit},
        {"env", _myenv},
        {"help", _myhelp},
        {"history", _myhistory},
        {"setenv", _mysetenv},
        {"unsetenv", _myunsetenv},
        {"cd", _mycd},
        {"alias", _myalias},
        {NULL, NULL}};

    for (i = 0; builtintbl[i].type; i++)
        if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
        {
            info->line_count++;
            built_in_ret = builtintbl[i].func(info);
            break;
        }
    return (built_in_ret);
}

/**
 * findCommand - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void findCommand(info_t *info)
{
    char *path = NULL;
    int i, k;

    info->path = info->argv[0];
    if (info->linecount_flag == 1)
    {
        info->line_count++;
        info->linecount_flag = 0;
    }
    for (i = 0, k = 0; info->arg[i]; i++)
        if (!is_delim(info->arg[i], " \t\n"))
            k++;
    if (!k)
        return;

    path = findPath(info, _getenv(info, "PATH="), info->argv[0]);
    if (path)
    {
        info->path = path;
        forkCommand(info);
    }
    else
    {
        if ((interactive(info) || _getenv(info, "PATH=") ||
             info->argv[0][0] == '/') &&
            isCmd(info, info->argv[0]))
            forkCommand(info);
        else if (*(info->arg) != '\n')
        {
            info->status = 127;
            printError(info, "not found\n");
        }
    }
}

/**
 * forkCommand - forks an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void forkCommand(info_t *info)
{
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == -1)
    {
        /* TODO: PUT ERROR FUNCTION */
        perror("Error:");
        return;
    }
}
