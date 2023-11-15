#include "shell.h"

int execute_command(char *command) {
    pid_t pid;
    int status;

    /* Tokenize the command into arguments */
    char *args[BUFFER_SIZE];
    strtok(command, " ");

    char *path = getenv("PATH");
    if (path == NULL){
    fprintf(stderr, "Error getting PATH\n");
    return 1; 
    }

    dir = strtok(path, ":");
    while (dir != NULL) {
        char path_buffer[BUFFER_SIZE];
        snprintf(path_buffer, BUFFER_SIZE, "%s/%s", dir, args[0]);

        if (access(path_buffer, X_OK) == 0) {
            /* The command exists, execute it */
            pid = fork();
            if (pid == 0) {
                /* Child process */
                execvp(path_buffer, args);
                /* If execvp fails, the following code will be executed */
                perror("simple_shell");
                exit(EXIT_FAILURE);
            } else if (pid < 0) {
                /* Handle fork error in the parent process */
                perror("simple_shell");
                return 1;  /* Return 1 to indicate an error */
            } else {
                /* Parent process */
                /* Wait for the child process to finish */
                waitpid(pid, &status, 0);
                return 1;
            }
        }

        dir = strtok(NULL, ":");
    }

    /* If the command doesn't exist in any of the PATH directories */
    fprintf(stderr, "Command not found: %s\n", args[0]);
    return 1;
}

