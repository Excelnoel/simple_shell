#include "shell.h"

/**
 * customStrcpy - Copies a string
 * @destination: The destination buffer
 * @source: The source string
 *
 * Return: Pointer to the destination buffer
 */
char *customStrcpy(char *destination, char *source)
{
    int index = 0;

    if (destination == source || source == NULL)
        return destination;

    while (source[index])
    {
        destination[index] = source[index];
        index++;
    }

    destination[index] = '\0';
    return destination;
}

/**
 * customStrdup - Duplicates a string
 * @str: The string to duplicate
 *
 * Return: Pointer to the duplicated string
 */
char *customStrdup(const char *str)
{
    int length = 0;
    char *result;

    if (str == NULL)
        return NULL;

    while (*str++)
        length++;

    result = malloc(sizeof(char) * (length + 1));

    if (!result)
        return NULL;

    for (length++; length--;)
        result[length] = *--str;

    return result;
}

/**
 * customPuts - Prints a string to stdout
 * @str: The string to be printed
 *
 * Return: Nothing
 */
void customPuts(char *str)
{
    int index = 0;

    if (!str)
        return;

    while (str[index] != '\0')
    {
        customPutchar(str[index]);
        index++;
    }
}

/**
 * customPutchar - Writes the character to stdout
 * @character: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int customPutchar(char character)
{
    static int bufferIndex;
    static char buffer[WRITE_BUF_SIZE];

    if (character == BUF_FLUSH || bufferIndex >= WRITE_BUF_SIZE)
    {
        write(1, buffer, bufferIndex);
        bufferIndex = 0;
    }

    if (character != BUF_FLUSH)
        buffer[bufferIndex++] = character;

    return 1;
}

