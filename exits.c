#include "shell.h"
/**
 * my_strncpy - Custom string copy function
 * @destination: The destination string to copy to
 * @source: The source string to copy from
 * @max_length: The maximum number of characters to copy 
 * Return: A pointer to the modified destination string
 */
char *my_strncpy(char *destination, char *source, int max_length)
{
	int dest_index = 0, src_index = 0;
	char *result = destination;

	while (source[src_index] != '\0' && src_index < max_length - 1)
	{
		destination[dest_index] = source[src_index];
		dest_index ++;
		src_index++;
	
	}
	if (src_index < max_length)
	{
		while (dest_index < max_length)
		{
			destination[dest_index] = '\0';
			dest_index++;
		}
	}
	return result;
}

/**
 * my_strncat - Custom string concatenation function
 * @destination: The first string
 * @source: The second string to append
 * @max_length: The maximum number of bytes to use
 * Return: A pointer to the concatenated string
 */
 
char *my_strncat(char *destination, char *source, int max_length)
{
	int dest_index = 0, src_index = 0;
	char *result = destination;

	
	while (destination[dest_index] != '\0')
	       dest_index++;

	while (source[src_index] != '\0' && src_index < max_length)
	{
		destination[dest_index] = source[src_index];
		dest_index++;
		src_index++;
	}
	if (src_index < max_length)
		destination[dest_index] = '\0';

	return result;
}

/**
 * my_strchr - Custom string character search function
 * @str: The string to search in
 * @character: The character to locate
 * Return: A pointer to the memory area in 'str' containing 'character'
 */
char *my_strchr(char *str, char character)
{
	do {
		if (*str == character)
			return str;
	} while (*str++ != '\0');

	return NULL;
}


 
