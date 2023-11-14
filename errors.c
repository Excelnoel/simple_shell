#include "shell.h"
/*
 * custom_puts - print a string to standard error
 * @str: the string to be printed
 * Return: None
 */
void custom_puts(char *str) {

	int index = 0;

	if (!str)
		return;

	while (str[index] != '\0') {
		custom_putchar(str[index]);
		index++;
	}
}
/**
 * custom_putchar - Write a character to standard error
 * @c: The character to print
 * Return: 1 on success, -1 on error
 */
int custom_putchar(char c) {

	static int buffer_index;
	static char output_buffer[OUTPUT_BUFFER_SIZE];

	if (c == FLUSH_BUFFER || buffer_index >= OUTPUT_BUFFER_SIZE) {
	
		write(STDERR_FILENO, output_buffer, buffer_index);
		buffer_index = 0;
	}

	if (c != FLUSH_BUFFER)
		output_buffer[buffer_index++] = c;

	return 1;
}
/**
 * custom_put_to_fd - writes a character to a specified file descriptor 
 * @c: the character to print
 * @fd: the file descriptor to write to
 * Return: 1 on success, -1 on error
 */
int custom_put_to_fd(char *str, int fd) {
	


	static int buffer_index;
	static char output_buffer[OUTPUT_BUFFER_SIZE];

	if (c == FLUSH_BUFFER || buffer_index >= OUTPUT_BUFFER_SIZE) {
	
		write(fd, output_buffer, buffer_index);
		buffer_index = 0;
	}
	if (c != FLUSH_BUFFER)
		output_buffer[buffer_index++] = c;

	return 1;
}
/**
 * custom_puts_to_fd - print a string to a specified file descriptor.
 * @str: The string to be printed
 * @fd: The file descriptor to write to
 * Return: The number of characters written
 */
int custom_puts_to_fd(char *str, int fd) {

	int char_count = 0;

	if (!str)
		return 0;
		
	char_count = write(fd, str, strlen(str));
	
	return char_count;
}
