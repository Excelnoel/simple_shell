builtin.c New Code

#include "shell.h"

/**
 * exit_shell - Exits the shell with a given exit status.
 * @info: Information structure containing potential arguments.
 * Return: 0 if info->argv[0] is not "exit".
 */
int exit_shell(info_t *info)
{
    int exit_status;

    if (info->argv[1])  /* Check if there is an exit argument */
    {
        exit_status = atoi(info->argv[1]);
        if (exit_status == -1)
        {
            info->status = 2;
            print_error(info, "Invalid number: ");
            _eputs(info->argv[1]);
            _eputchar('\n');
            return 1;
        }
        info->err_num = exit_status;
        return -2;
    }
    info->err_num = -1;
    return -2;
}

/**
 * change_directory - Changes the current directory of the process.
 * @info: Information structure containing potential arguments.
 * Return: Always returns 0.
 */
int change_directory(info_t *info)
{
    char *current_dir, *target_dir, buffer[1024];
    int chdir_result;

    current_dir = getcwd(buffer, 1024);
    if (!current_dir)
        _puts("TODO: Handle getcwd failure here\n");
    
    if (!info->argv[1])
    {
        target_dir = _getenv(info, "HOME=");
        if (!target_dir)
            chdir_result = chdir((target_dir = _getenv(info, "PWD=")) ? target_dir : "/");
        else
            chdir_result = chdir(target_dir);
    }
    else if (_strcmp(info->argv[1], "-") == 0)
    {
        if (!_getenv(info, "OLDPWD="))
        {
            _puts(current_dir);
            _putchar('\n');
            return 1;
        }
        _puts(_getenv(info, "OLDPWD="));
        _putchar('\n');
        chdir_result = chdir((target_dir = _getenv(info, "OLDPWD=")) ? target_dir : "/");
    }
    else
        chdir_result = chdir(info->argv[1]);
    
    if (chdir_result == -1)
    {
        print_error(info, "Can't change directory to ");
        _eputs(info->argv[1]);
        _eputchar('\n');
    }
    else
    {
        _setenv(info, "OLDPWD", _getenv(info, "PWD="));
        _setenv(info, "PWD", getcwd(buffer, 1024));
    }
    
    return 0;
}

/**
 * display_help - Displays help for the shell.
 * @info: Information structure containing potential arguments.
 * Return: Always returns 0.
 */
int display_help(info_t *info)
{
    char **arguments;

    arguments = info->argv;
    _puts("Help function is called. Function not yet implemented.\n");
    if (0)
        _puts(*arguments); /* Temporary unused variable workaround */
    return 0;
}


