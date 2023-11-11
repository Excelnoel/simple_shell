#include "shell.h"

/**
 * customMemset - Fills memory with a constant byte
 * @memory: Pointer to the memory area
 * @value: The byte to fill @memory with
 * @size: The number of bytes to be filled
 *
 * Return: A pointer to the memory area @memory
 */
char *customMemset(char *memory, char value, unsigned int size)
{
    unsigned int i;

    for (i = 0; i < size; i++)
        memory[i] = value;

    return memory;
}

/**
 * freeStringArray - Frees a string array
 * @strArray: The string array to be freed
 */
void freeStringArray(char **strArray)
{
    char **temp = strArray;

    if (!strArray)
        return;

    while (*strArray)
        free(*strArray++);

    free(temp);
}

/**
 * customRealloc - Reallocates a block of memory
 * @ptr: Pointer to the previous dynamically allocated block
 * @oldSize: Byte size of the previous block
 * @newSize: Byte size of the new block
 *
 * Return: Pointer to the reallocated block of memory
 */
void *customRealloc(void *ptr, unsigned int oldSize, unsigned int newSize)
{
    char *newPtr;

    if (!ptr)
        return malloc(newSize);

    if (!newSize)
        return (free(ptr), NULL);

    if (newSize == oldSize)
        return ptr;

    newPtr = malloc(newSize);

    if (!newPtr)
        return NULL;

    oldSize = oldSize < newSize ? oldSize : newSize;

    while (oldSize--)
        newPtr[oldSize] = ((char *)ptr)[oldSize];

    free(ptr);
    return newPtr;
}

