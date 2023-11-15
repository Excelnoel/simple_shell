#include "shell.h"

extern char **environ;  /* Declare environ */

void display_prompt() {
    printf("#cisfun$ ");
    fflush(stdout);
}

int execute_command(char *command) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {

	/* Tokenize the command into arguments */
        char *args[BUFFER_SIZE];  
	char *token = strtok(command, " ");
        int i = 0;

        while (token != NULL && i < BUFFER_SIZE - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }

        args[i] = NULL;  /* Null-terminate the array */

        /* Execute the command in the child process */
        if (execvp(args[0], args) == -1) {
            perror("simple_shell");
            exit(EXIT_FAILURE);
        }
    } else if (pid < 0) {
        /* Handle fork error in the parent process */
        perror("simple_shell");
        return 1;  /* Return 1 to indicate an error */
    } else {
        /* Parent process */

        /* Wait for the child process to finish */
        waitpid(pid, &status, 0);
    }

    return 1;
}

