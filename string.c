#include "shell.h"

/**
 * getStringLength - Calculates the length of a string
 * @str: The string to measure
 *
 * Returns: The length of the string
 */
int getStringLength(char *str)
{
    int length = 0;

    if (!str)
        return 0;

    while (*str++)
        length++;

    return length;
}

/**
 * compareStrings - Performs lexicographic comparison of two strings
 * @s1: The first string
 * @s2: The second string
 *
 * Returns: Negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int compareStrings(char *s1, char *s2)
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
 * startsWithString - Checks if needle starts with haystack
 * @haystack: The string to search
 * @needle: The substring to find
 *
 * Returns: Address of the next character in haystack or NULL
 */
char *startsWithString(const char *haystack, const char *needle)
{
    while (*needle)
        if (*needle++ != *haystack++)
            return NULL;

    return (char *)haystack;
}

/**
 * concatenateStrings - Concatenates two strings
 * @destination: The destination buffer
 * @source: The source buffer
 *
 * Returns: Pointer to the destination buffer
 */
char *concatenateStrings(char *destination, char *source)
{
    char *result = destination;

    while (*destination)
        destination++;

    while (*source)
        *destination++ = *source++;

    *destination = *source;

    return result;
}

