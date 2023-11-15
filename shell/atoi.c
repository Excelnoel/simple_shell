#include "shell.h"
/**
 * error_atoi - converts str to integer
 * @str: string
 * Return: 0 if not str otherwise -1
 *
 */
int error_atoi(char *str)
{
	int i = 0;
	unsigned long int rslt = 0;

	if (*str == '+')
		str++;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			rslt *= 10;
			rslt += (str[i] - '0');
			if (rslt > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (rslt);
}
