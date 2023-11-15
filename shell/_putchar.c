#include "shell.h"
/**
 * eput_char - prints char c to stderror
 * @c: char
 * Return: 1 if success, otherwise -1 on error
 *
 */
int eput_char(char c)
{
	static int i;
	static char buffer[GET_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= GET_BUFFER_SIZE)
	{
		write(2, buffer, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[i++] = c;
	return (1);
}
