#include "shell.h"

/**
 * customStrlen - Calculates the length of a string
 * @str: The string to measure
 *
 * Return: The length of the string
 */
int customStrlen(char *str)
{
    int length = 0;

    if (!str)
        return 0;

    while (*str++)
        length++;

    return length;
}

/**
 * customStrcmp - Performs lexicographic comparison of two strings
 * @s1: The first string
 * @s2: The second string
 *
 * Return: Negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int customStrcmp(char *s1, char *s2)
{
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
            return (*s1 - *s2);

        s1++;
        s2++;
    }

    if (*s1 == *s2)
        return 0;
    else
        return (*s1 < *s2 ? -1 : 1);
}

/**
 * startsWith - Checks if needle starts with haystack
 * @haystack: The string to search
 * @needle: The substring to find
 *
 * Return: Address of the next character in haystack or NULL
 */
char *startsWith(const char *haystack, const char *needle)
{
    while (*needle)
        if (*needle++ != *haystack++)
            return NULL;

    return (char *)haystack;
}

/**
 * customStrcat - Concatenates two strings
 * @dest: The destination buffer
 * @src: The source buffer
 *
 * Return: Pointer to the destination buffer
 */
char *customStrcat(char *dest, char *src)
{
    char *result = dest;

    while (*dest)
        dest++;

    while (*src)
        *dest++ = *src++;

    *dest = *src;

    return result;
}

