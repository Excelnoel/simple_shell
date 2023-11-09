#include "shell.h"
/**
 * check_if_interactive - checks if the shell is running in interactive mode.
 * @shell_info: A structure holding information about the shell.
 * Return: 1 if in interactive mode, 0 otherwise.
 */
int check_if_interactive(ShellInfo_t *shell_info)
{
	return (isatty(STDIN_FILENO) && shell_info->read_fd <= 2);
}
/**
 * is_delimiter - Checks if a character is a delimeter.
 * @character: The character to check.
 * @delimiters: the delimeter string.
 * Return: 1 if it's a delimeter, 0 otherwise.
 */
int is_delimiter(char character, char *delimiters)
{
	while (*delimiters)
		if (*delimiters++ == character)
			return 1;
	return 0;
}
/**
 * is_alpha - Checks if a character is an alphabetic character.
 * @character: The character to check
 * Return: 1 if c is alphabetic, 0 otherwise.
 */
int is_alpha(int character)
{
	if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'))
		return 1;
	else
		return 0;
}
/**
 * string_to_int - converts a string to an integer.
 * @str: The string to be converted
 * Return: 0 if there are no numbers in the string, the converted number otherwise.
 */
int string_to_int(char *str)
{
	int i, sign = 1, number_flag = 0, result = 0;
	unsigned int parsed_number = 0;

	for (i = 0; str[i] != '\0' && number_flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;
		if (str[i] >= '0' && str[i] <= '9')
		{
			number_flag = 1;
			parsed_number *= 10;
			parsed_number += (str[i] - '0');
		}
		else if (number_flag == 1)
			number_flag = 2;
	}
	if (sign == -1)
		result = -parsed_number;
	else
		result = parsed_number;
	return result;
}

