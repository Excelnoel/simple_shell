#include "shell.h"
/**
 * gets_buffer - reads the buffer
 * @buffer: buffer itself
 * @i: size
 * @data: storage struct
 * Return: n
 *
 */
ssize_t gets_buffer(data_t *data, char *buffer, size_t *i)
{
	ssize_t n = 0;

	if (*i)
		return (0);
	n = read(data->gets_fd, buffer, READ_BUFFER_SIZE);
	if (n >= 0)
		*i = n;
	return (n);
}
