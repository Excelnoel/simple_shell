#include "shell.h"
/**
 * check_alpha - checks for alphabetic char
 * @c: input char
 * Return: 1 if char is alpha, otherwise 0
 *
 *
 */
int check_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
