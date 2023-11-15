#include "shell.h"
/**
 * gets_fd - prints file description
 * @str: string
 * @fd: file descriptor
 * Return: char input
 *
 */
int gets_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += get_fd(*str++, fd);
	}
	return (i);
}
