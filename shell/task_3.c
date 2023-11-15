#include "shell.h"

int main(void) {
    char *buffer = NULL; 
    ssize_t read_bytes;
    size_t buffer_len = 0;

    while (1) {
        display_prompt();

        /* Read a line of input */
        read_bytes = getline(&buffer, &buffer_len, stdin);
        if (read_bytes == -1) {
            if (feof(stdin)) {
                /* Handle EOF (Ctrl+D) */
                printf("\n");
                break;
            } else {
                perror("simple_shell");
                exit(EXIT_FAILURE);
            }
        }

        /* Remove the newline character */
        buffer[strcspn(buffer, "\n")] = '\0';

        /* Execute the command */
        if (execute_command(buffer) == 0) {
            break; /* Exit the shell */
        }
    }

    /* Free the allocated memory for buffer */
    free(buffer);

    return EXIT_SUCCESS;
}
