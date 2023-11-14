#ifndef _SHELL_H_
#define _SHELL_H_

#define OUTPUT_BUFFER_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define FLUSH_BUFFER -1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Read and write buffer sizes */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Command chaining types */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* Conversion types for convertToNumber() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* Flag for using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

/* History file configuration */
#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

/* External environment variable */
extern char **environ;

/* Structure for singly linked list of strings */
typedef struct liststr
{
    int num;
    char *str;
    struct liststr *next;
} list_t;

/* Structure for passing information to functions */
typedef struct passinfo
{
    char *arg;
    char **argv;
    char *path;
    int argc;
    unsigned int line_count;
    int err_num;
    int linecount_flag;
    char *fname;
    list_t *env;
    list_t *history;
    list_t *alias;
    char **environ;
    int env_changed;
    int status;
    char **cmd_buf;
    int cmd_buf_type;
    int readfd;
    int histcount;
} info_t;

/* Macro for initializing info_t structure */
#define INFO_INIT \
    {NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
    0, 0, 0 }

/* Structure for built-in commands */
typedef struct builtin
{
    char *type;
    int (*func)(info_t *);
} builtin_table;

/* Custom error handling and output functions */
void custom_puts(char *str);
int custom_putchar(char c);
int custom_put_to_fd(char *, int fd);
int custom_puts_to_fd(char *, int fd);

/* Built-in command functions */
int exitShell(info_t *);
int changeDirectory(info_t *);
int displayHelp(info_t *);
int _erratoi(info_t *);
int displayHistory(info_t *);
int manageAlias(info_t *);

/* Input and output functions */
ssize_t bufferInput(info_t *params, char **buffer, size_t *length);
int getLine(info_t *, char **, size_t *);
void handleSigint(int);
void interruptHandler(__attribute__((unused)) int signum);

/* String manipulation functions */
void printErrorMessage(char *);
int printErrorCharacter(char);
int putCharacterToFile(char c, int fd);
int putStringToFile(char *str, int fd);
int stringLength(char *);
int stringCompare(char *, char *);
char *startsWith(const char *, const char *);
char *stringConcatenate(char *, char *);
char *stringCopy(char *, char *);
char *stringDuplicate(const char *);
void printString(char *);
int printCharacter(char);

/* Memory manipulation functions */
char *memorySet(char *, char, unsigned int);
void freeMemory(char **);
void *reallocateMemory(void *, unsigned int, unsigned int);
int freeBlock(void **);

/* Numeric conversion and error handling functions */
int handleInteractive(info_t *);
int isDelimiter(char, char *);
int isAlpha(int);
int convertToInteger(char *);
int errorAtoi(char *);
void printErrorInfo(info_t *, char *);
int printDecimal(int, int);
char *convertToNumber(long int, int, int);
void removeComments(char *);

/* History-related functions */
void clearInfo(info_t *);
int interactive(info_t *);
void _puts(const char *);
void _eputchar(char);
ssize_t getInput(info_t *);
void setInfo(info_t *, char **);
void freeInfo(info_t *, int);
char *findPath(info_t *, char *, char *);
void printError(info_t *, char *);
int isChainDelimiter(info_t *, char *, size_t *);
void checkChain(info_t *, char *, size_t *, size_t, size_t);
int replaceAliases(info_t *);
int replaceVariables(info_t *);
int replaceString(char **, char *);
void _eputs(const char *);
void _eputchar(char);
void populate_env_list(info_t *);
void read_history(info_t *);
void hsh(info_t *, char **);

/* History-related functions (continued) */
int writeHistory(info_t *);
int readHistory(info_t *);
int buildHistoryList(info_t *, char *, int);
int renumberHistory(info_t *);

/* Linked list manipulation functions */
list_t *addNode(list_t **, const char *, int);
list_t *addNodeEnd(list_t **, const char *, int);
size_t printListString(const list_t *);
int deleteNodeAtIndex(list_t **, unsigned int);
void freeList(list_t **);

/* Linked list manipulation functions (continued) */
size_t getListLength(const list_t *);
char **listToStrings(list_t *);
size_t printList(const list_t *);
list_t *nodeStartsWith(list_t *, char *, char);
ssize_t getNodeIndex(list_t *, list_t *);

/* Environment variable-related functions */
int isCmd(info_t *, const char *);
char *getEnvironmentVariable(info_t *, const char *);
int executeEnvironmentCommand(info_t *);
int setEnvironmentVariable(info_t *);
int unsetEnvironmentVariable(info_t *);
int populateEnvironmentList(info_t *);
char **getEnvironment(info_t *);
int unsetEnvironmentVariables(info_t *, char *);
int setEnvironmentVariables(info_t *, char *, char *);

#endif /* _SHELL_H_ */

