#include "shell.h"

/**
 * generateHistoryFilePath - Generates the history file path
 * @info: Parameter struct
 * Return: Allocated string containing the history file path
 */
char *generateHistoryFilePath(info_t *info)
{
    char *homeDir = _getenv(info, "HOME=");

    if (!homeDir)
        return NULL;

    char *filePath = malloc(sizeof(char) * (_strlen(homeDir) + _strlen(HIST_FILE) + 2));
    
    if (!filePath)
        return NULL;

    filePath[0] = 0;
    _strcpy(filePath, homeDir);
    _strcat(filePath, "/");
    _strcat(filePath, HIST_FILE);

    return filePath;
}

/**
 * writeHistoryToFile - Creates a file or appends to an existing file
 * @info: Parameter struct
 * Return: 1 on success, else -1
 */
int writeHistoryToFile(info_t *info)
{
    ssize_t fd;
    char *filename = generateHistoryFilePath(info);
    list_t *node = NULL;

    if (!filename)
        return -1;

    fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);

    if (fd == -1)
        return -1;

    for (node = info->history; node; node = node->next)
    {
        _putsfd(node->str, fd);
        _putfd('\n', fd);
    }

    _putfd(BUF_FLUSH, fd);
    close(fd);

    return 1;
}

/**
 * readHistoryFromFile - Reads history from the file
 * @info: Parameter struct
 * Return: Histcount on success, 0 otherwise
 */
int readHistoryFromFile(info_t *info)
{
    int i, last = 0, linecount = 0;
    ssize_t fd, rdlen, fsize = 0;
    struct stat st;
    char *buf = NULL, *filename = generateHistoryFilePath(info);

    if (!filename)
        return 0;

    fd = open(filename, O_RDONLY);
    free(filename);

    if (fd == -1)
        return 0;

    if (!fstat(fd, &st))
        fsize = st.st_size;

    if (fsize < 2)
        return 0;

    buf = malloc(sizeof(char) * (fsize + 1));

    if (!buf)
        return 0;

    rdlen = read(fd, buf, fsize);
    buf[fsize] = 0;

    if (rdlen <= 0)
        return free(buf), 0;

    close(fd);

    for (i = 0; i < fsize; i++)
        if (buf[i] == '\n')
        {
            buf[i] = 0;
            buildHistoryList(info, buf + last, linecount++);
            last = i + 1;
        }

    if (last != i)
        buildHistoryList(info, buf + last, linecount++);

    free(buf);
    info->histcount = linecount;

    while (info->histcount-- >= HIST_MAX)
        deleteNodeAtIndex(&(info->history), 0);

    renumberHistory(info);

    return info->histcount;
}

/**
 * buildHistoryList - Adds an entry to a history linked list
 * @info: Structure containing potential arguments used for maintaining
 * @buf: Buffer
 * @linecount: The history linecount, histcount
 * Return: Always 0
 */
int buildHistoryList(info_t *info, char *buf, int linecount)
{
    list_t *node = NULL;

    if (info->history)
        node = info->history;

    addNodeEnd(&node, buf, linecount);

    if (!info->history)
        info->history = node;

    return 0;
}

/**
 * renumberHistory - Renumbers history linked list after changes
 * @info: Structure containing potential arguments
 * Return: The new histcount
 */
int renumberHistory(info_t *info)
{
    list_t *node = info->history;
    int i = 0;

    while (node)
    {
        node->num = i++;
        node = node->next;
    }

    return info->histcount = i;
}

