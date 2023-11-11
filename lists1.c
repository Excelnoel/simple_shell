#include "shell.h"

/**
 * getLinkedListLength - determines the length of a linked list
 * @head: pointer to the first node
 *
 * Return: size of the list
 */
size_t getLinkedListLength(const list_t *head)
{
    size_t count = 0;

    while (head)
    {
        head = head->next;
        count++;
    }
    return count;
}

/**
 * linkedListToStrings - returns an array of strings from the list nodes
 * @head: pointer to the first node
 *
 * Return: array of strings
 */
char **linkedListToStrings(list_t *head)
{
    list_t *current = head;
    size_t length = getLinkedListLength(head), index;
    char **strings;
    char *str;

    if (!head || !length)
        return NULL;

    strings = malloc(sizeof(char *) * (length + 1));
    if (!strings)
        return NULL;

    for (index = 0; current; current = current->next, index++)
    {
        str = malloc(_strlen(current->str) + 1);
        if (!str)
        {
            for (size_t j = 0; j < index; j++)
                free(strings[j]);
            free(strings);
            return NULL;
        }

        str = _strcpy(str, current->str);
        strings[index] = str;
    }

    strings[index] = NULL;
    return strings;
}

/**
 * printLinkedList - prints all elements of a list_t linked list
 * @head: pointer to the first node
 *
 * Return: size of the list
 */
size_t printLinkedList(const list_t *head)
{
    size_t count = 0;

    while (head)
    {
        _puts(convert_number(head->num, 10, 0));
        _putchar(':');
        _putchar(' ');
        _puts(head->str ? head->str : "(nil)");
        _puts("\n");
        head = head->next;
        count++;
    }
    return count;
}

/**
 * findNodeWithPrefix - returns a node whose string starts with a prefix
 * @head: pointer to the list head
 * @prefix: string to match
 * @c: the next character after the prefix to match
 *
 * Return: matching node or NULL
 */
list_t *findNodeWithPrefix(list_t *head, char *prefix, char c)
{
    char *result = NULL;

    while (head)
    {
        result = starts_with(head->str, prefix);
        if (result && ((c == -1) || (*result == c)))
            return head;
        head = head->next;
    }
    return NULL;
}

/**
 * getNodeIndex - gets the index of a node in a linked list
 * @head: pointer to the list head
 * @node: pointer to the node
 *
 * Return: index of the node or -1
 */
ssize_t getNodeIndex(list_t *head, list_t *node)
{
    size_t index = 0;

    while (head)
    {
        if (head == node)
            return index;
        head = head->next;
        index++;
    }
    return -1;
}

