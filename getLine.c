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

        ssize_t bytes_read =0;
        size_t length_p = 0;

        if (!*length) {
                free(*buffer);
                *buffer = NULL;
                signal(SIGINT, interruptHandler);
        #if USE_GETLINE
                bytes_read = getline(buffer &length_p, stdin);
        #else
                bytes_read = customGetLine(params, buffer, &length_p);
        #endif
                if (bytes_read > 0) {
                        if ((*buffer)[bytes_read - 1] == '\n') {
                                (*buffer)[bytes_read - 1] = '\0'; // Remove trailing newline
                                bytes_read--;
                        }

                        params->line_count_flag = 1;
                        removeComments(*buffer);
                        buildHistoryList(params, *buffer, params->history_count++);
                        // Check for command chaining
                        {
                                *length = bytes_read;
                                params->command_buffer = buffer;
                        }
                }
        }
        return bytes_read;
}

/**
 * getInput - gets a line without the newline character
 * @params: parameter struct
 * Rerurn: bytes read
 */
ssize_t getInput(info_t *info) {
{
        static char *command_buffer; //The ';' command chain buffer
        static size_t i, j, length;
        ssize_t bytes_read = 0;
        char **command_buffer_ptr = &(params->arguements);
        char *current-position;

        _putchar(BUF_FLUSH);
        bytes_read = bufferInput(params, &command_buffer, &length);info, &buf, 
        if (bytes_read == -1) // EOF
                return-1;

        if (length) { We have commands left in the chain buffer
        {
                j = i; // initialize new iterator to current buffer position
                current_position = command_buffer + i; Get pointer for return

                checkCommandChain(params, command_buffer, &j, i, length);

                while (j < length) { // Iterate to semicolon or end 

                        if (isCommandChain(params, command_buffer, &j))
                                break;
                        j++;
                }

                i = j + 1; // Increment past nullified ';''
                if (i >= length) { // Reached the end of the buffer

                        i = length = 0; // Reset position and length 
                        params->command_buffer_type = CMD_NORM;
                }

                *command_buffer_ptr = current position; // Pass back a pointer to the current command position
                return (_strlen(current_position); // Return the length of current command 
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
        bytes_read = read(params->read_fd, buf, READ_BUF_SIZE);
        if (bytes_read >= 0)
                *i = bytes_read;
        return bytes_read;
}
/**
 * CustomGetLine - gets the next line of input from STDIN
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

        bytes_read = readBuf(params, buf, &len);
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
void interruptHandler(__attribute__((unused))int signum) {

        _puts("\n");
        _puts("$ ");
        _putchar(BUF_FLUSH);
}

