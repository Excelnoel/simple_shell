#include "shell.h"

/**
 * splitString - Splits a string into words, ignoring repeat delimiters
 * @inputStr: The input string
 * @delimiters: The delimiter string
 * Return: Pointer to an array of strings, or NULL on failure
 */
char **splitString(char *inputStr, char *delimiters)
{
    int i, j, k, m, numWords = 0;
    char **resultArray;

    if (inputStr == NULL || inputStr[0] == 0)
        return NULL;

    if (!delimiters)
        delimiters = " ";

    for (i = 0; inputStr[i] != '\0'; i++)
        if (!isDelimiter(inputStr[i], delimiters) && (isDelimiter(inputStr[i + 1], delimiters) || !inputStr[i + 1]))
            numWords++;

    if (numWords == 0)
        return NULL;

    resultArray = malloc((1 + numWords) * sizeof(char *));
    if (!resultArray)
        return NULL;

    for (i = 0, j = 0; j < numWords; j++)
    {
        while (isDelimiter(inputStr[i], delimiters))
            i++;

        k = 0;

        while (!isDelimiter(inputStr[i + k], delimiters) && inputStr[i + k])
            k++;

        resultArray[j] = malloc((k + 1) * sizeof(char));
        if (!resultArray[j])
        {
            for (k = 0; k < j; k++)
                free(resultArray[k]);

            free(resultArray);
            return NULL;
        }

        for (m = 0; m < k; m++)
            resultArray[j][m] = inputStr[i++];

        resultArray[j][m] = 0;
    }

    resultArray[j] = NULL;
    return resultArray;
}

/**
 * splitString2 - Splits a string into words using a single delimiter
 * @inputStr: The input string
 * @delimiter: The delimiter character
 * Return: Pointer to an array of strings, or NULL on failure
 */
char **splitString2(char *inputStr, char delimiter)
{
    int i, j, k, m, numWords = 0;
    char **resultArray;

    if (inputStr == NULL || inputStr[0] == 0)
        return NULL;

    for (i = 0; inputStr[i] != '\0'; i++)
        if ((inputStr[i] != delimiter && inputStr[i + 1] == delimiter) ||
            (inputStr[i] != delimiter && !inputStr[i + 1]) || inputStr[i + 1] == delimiter)
            numWords++;

    if (numWords == 0)
        return NULL;

    resultArray = malloc((1 + numWords) * sizeof(char *));
    if (!resultArray)
        return NULL;

    for (i = 0, j = 0; j < numWords; j++)
    {
        while (inputStr[i] == delimiter && inputStr[i] != delimiter)
            i++;

        k = 0;

        while (inputStr[i + k] != delimiter && inputStr[i + k] && inputStr[i + k] != delimiter)
            k++;

        resultArray[j] = malloc((k + 1) * sizeof(char));
        if (!resultArray[j])
        {
            for (k = 0; k < j; k++)
                free(resultArray[k]);

            free(resultArray);
            return NULL;
        }

        for (m = 0; m < k; m++)
            resultArray[j][m] = inputStr[i++];

        resultArray[j][m] = 0;
    }

    resultArray[j] = NULL;
    return resultArray;
}

