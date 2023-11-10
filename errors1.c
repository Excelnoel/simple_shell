#include "shell.h"
/**
 * _err_atoi - converts string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 * 		-1 on error
 */
int err_atoi(char *str) {

	int index = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;

	for (index = 0; str[index] != '\0'; index++) {
	
		if (str[index] >= '0' && s[index] <= '9') {
		
			result *= 10;
			result += (str[index] - '0');
			if (result > INT_MAX)
				return (-1);
		} else {
			return (-1);
	}
}
	return result;
}
/**
 * print_error - printing an error message
 * @info_struct: The parameter & return info struct
 * @error_str: string containing the specified error type.
 */
void print_error(info_t *info_struct, char *error_str) {

	_eputs(info_struct->fname);
	_eputs(": ");
	print_d(info_struct->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info_struct->argv[0]);
	_eputs(": ");
	_eputs(error_str);
}
/**
 * print_decimal - function prints a decimal number. 
 * @num: The input number.
 * @fd: The filedescriptor to write to.
 * Return: number of characters printed
 */
int print_decimal(int num, int fd) {

	int (*custom_putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int absolute_value, current;

	if (fd == STDERR_FILENO)
		custom_putchar = _eputchar;

	if (num < 0) {
		absolute_value = -num;
		custom_putchar('-');
		count++;
	} else {
		absolute_value = num;
	}
	current = absolute_value;

	for (i = 1000000000; i > 1; i /= 10) {
		if (absolute_value / i) {
			custom_putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	custom_putchar('0' + current);
	count++;

	return count;
}

/**
 * convert_number - converter function, similar of itoa
 * @num: number to convert
 * @base:  The base for conversion.
 * @flags: Arguement flags.
 * Return: The converted string.
 */
char *convert_number(long int num, int base, int flags) {

	static char *char_array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0) {
	
		n = -num;
		sign = '-';
	}
	char_array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = char_array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return ptr;
}

/**
 * remove_comments - Replaces the first instance of '#' with '\0'
 * @string: Address of the string to modify
 */
void remove_comments(char *string) {

	int i;

	for (i = 0; string[i] != '\0'; i++) {
		if (string[i] == '#' && (!i || string[i - 1] == ' ')) {
		
			string[i] = '\0';
			break;
		}
	}
}


