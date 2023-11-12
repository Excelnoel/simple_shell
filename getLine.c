#include "shell.h"
#include <signal.h>

/**
 * bufferInput - buffer input for chained commands
 * @params: parameter struct
 * @buffer: address of buffer
 * @length: address of length var
 * Return: bytes read
 */
ssize_t bufferInput(info_t *params, char **buffer, size_t *length) {
    ssize_t bytes_read = 0;
    size_t length_p = 0;

    if (!*length) {
        free(*buffer);
        *buffer = NULL;
        signal(SIGINT, interruptHandler);

#if USE_GETLINE
        // Corrected the arguments for getline
        bytes_read = getline(buffer, &length_p, stdin);
#else
        bytes_read = customGetLine(params, buffer, &length_p);
#endif

        if (bytes_read > 0) {
            if ((*buffer)[bytes_read - 1] == '\n') {
                (*buffer)[bytes_read - 1] = '\0'; // Remove trailing newline
                bytes_read--;
            }

            params->linecount_flag = 1;
            removeComments(*buffer);
            buildHistoryList(params, *buffer, params->histcount++);
            // Check for command chaining
            *length = bytes_read;
            params->command_buffer = *buffer; // Assign the pointer, not the value
        }
    }
    return bytes_read;
}

/**
 * getInput - gets a line without the newline character
 * @info: parameter struct
 * Return: bytes read
 */
ssize_t getInput(info_t *info) {
    static char *command_buffer; // The ';' command chain buffer
    static size_t i, length;
    ssize_t bytes_read = 0;
    char **command_buffer_ptr = &(info->argv);
    char *current_position;

    _putchar(BUF_FLUSH);
    // Corrected the function call arguments
    bytes_read = bufferInput(info, &command_buffer, &length);

    if (bytes_read == -1) // EOF
        return -1;

    if (length) { // We have commands left in the chain buffer
        i = 0; // Initialize iterator to start of buffer
        current_position = command_buffer; // Get pointer for return

        // Check for command chaining
        checkChain(info, command_buffer, &i, 0, length);

        while (i < length) { // Iterate to semicolon or end
            if (isChainDelimiter(info, command_buffer, &i))
                break;
            i++;
        }

        // Increment past nullified ';'
        i = i + 1;

        if (i >= length) { // Reached the end of the buffer
            i = length = 0; // Reset position and length
            info->cmd_buf_type = CMD_NORM;
        }

        *command_buffer_ptr = current_position; // Pass back a pointer to the current command position
        return (_strlen(current_position)); // Return the length of the current command
    }

    *command_buffer_ptr = command_buffer; // Not a chain, pass back the buffer from customGetLine()
    return bytes_read; // Return the length of the buffer from customGetLine()
}

/**
 * readBuffer - read a buffer
 * @params: parameter struct
 * @buf: buffer
 * @i: size
 * Return: r
 */
ssize_t readBuffer(info_t *params, char *buf, size_t *i) {
    ssize_t bytes_read = 0;

    if (*i)
        return (0);
    bytes_read = read(params->readfd, buf, READ_BUF_SIZE); // Corrected member name from read_fd to readfd
    if (bytes_read >= 0)
        *i = bytes_read;
    return bytes_read;
}

/**
 * customGetLine - gets the next line of input from STDIN
 * @params: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 * Return: s
 */
int customGetLine(info_t *params, char **ptr, size_t *length) {
    static char buf[READ_BUF_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t bytes_read = 0, s = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;
    if (p && length)
        s = *length;
    if (i == len)
        i = len = 0;

    bytes_read = readBuffer(params, buf, &len);
    if (bytes_read == -1 || (bytes_read == 0 && len == 0))
        return -1;

    c = _strchr(buf + i, '\n');
    k = c ? 1 + (unsigned int)(c - buf) : len;
    new_p = _realloc(p, s, s ? s + k : k + 1);
    if (!new_p) // MALLOC FAILURE
        return p ? free(p), -1 : -1;

    if (s)
        _strncat(new_p, buf + i, k - i);
    else
        _strncpy(new_p, buf + i, k - i + 1);

    s += k - i;
    i = k;
    p = new_p;

    if (length)
        *length = s;
    *ptr = p;
    return s;
}

/**
 * interruptHandler - block Ctrl-C
 * @signum: the signal number
 * Return: void
 */
void interruptHandler(__attribute__((unused)) int signum) {
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FLUSH);
}

