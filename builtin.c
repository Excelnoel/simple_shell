#include "shell.h"

/* Declarations */
int _erratoi(info_t *info);
void print_error(info_t *info, const char *message);
void _eputs(const char *str);
void _eputchar(char c);
void _puts(const char *str);
char *_getenv(info_t *info, const char *name);
int _strcmp(const char *s1, const char *s2);
void _putchar(char c);
void _setenv(info_t *info, const char *name, const char *value);

/* Function Definitions */

int exitShell(info_t *info)
{
        int exitcheck;

        if (info->argv[1])  /* If there is an exit argument */
        {
                exitcheck = _erratoi(info);
                if (exitcheck == -1)
                {
                        info->status = 2;
                        print_error(info, "Illegal number: ");
                        _eputs(info->argv[1]);
                        _eputchar('\n');
                        return (1);
                }
                info->err_num = _erratoi(info->argv[1]);
                return (-2);
        }
        info->err_num = _erratoi(info);
        return (-2);
}

int changeDirectory(info_t *info)
{
        char *s, *dir, buffer[1024];
        int chdir_ret;

        s = getcwd(buffer, 1024);
        if (!s)
                _puts("TODO: >>getcwd failure emsg here<<\n");
        if (!info->argv[1])
        {
                dir = _getenv(info, "HOME=");
                if (!dir)
                        chdir_ret = /* TODO: what should this be? */
                                chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
                else
                        chdir_ret = chdir(dir);
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
                chdir_ret = /* TODO: what should this be? */
                        chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
        }
        else
                chdir_ret = chdir(info->argv[1]);
        if (chdir_ret == -1)
        {
                print_error(info, "can't cd to ");
                _eputs(info->argv[1]), _eputchar('\n');
        }
        else
        {
                _setenv(info, "OLDPWD", _getenv(info, "PWD="));
                _setenv(info, "PWD", getcwd(buffer, 1024));
        }
        return (0);
}

int displayHelp(info_t *info)
{
        char **arg_array;
        arg_array = info->argv;
        _puts("help call works. Function not yet implemented \n");
        if (0)
                _puts(*arg_array); /* temp att_unused workaround */
        return (0);
}

