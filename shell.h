#ifndef _SHELL_H_
#define _SHELL_H_

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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
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

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* toem_shloop.c */
int shellLoop(info_t *, char **);
int findBuiltin(info_t *);
void findCommand(info_t *);
void forkCommand(info_t *);

/* toem_parser.c */
int isCommand(info_t *, char *);
char *duplicateChars(char *, int, int);
char *findPath(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void printErrorMessage(char *);
int printErrorCharacter(char);
int putCharacterToFile(char c, int fd);
int putStringToFile(char *str, int fd);

/* toem_string.c */
int stringLength(char *);
int stringCompare(char *, char *);
char *startsWith(const char *, const char *);
char *stringConcatenate(char *, char *);

/* toem_string1.c */
char *stringCopy(char *, char *);
char *stringDuplicate(const char *);
void printString(char *);
int printCharacter(char);

/* toem_exits.c */
char *stringCopyN(char *, char *, int);
char *stringConcatenateN(char *, char *, int);
char *stringFindCharacter(char *, char);

/* toem_tokenizer.c */
char **tokenizeString(char *, char *);
char **tokenizeStringWithDelimiter(char *, char);

/* toem_realloc.c */
char *memorySet(char *, char, unsigned int);
void freeMemory(char **);
void *reallocateMemory(void *, unsigned int, unsigned int);

/* toem_memory.c */
int freeBlock(void **);

/* toem_atoi.c */
int handleInteractive(info_t *);
int isDelimiter(char, char *);
int isAlpha(int);
int convertToInteger(char *);

/* toem_errors1.c */
int errorAtoi(char *);
void printErrorInfo(info_t *, char *);
int printDecimal(int, int);
char *convertToNumber(long int, int, int);
void removeComments(char *);

/* toem_builtin.c */
int exitShell(info_t *);
int changeDirectory(info_t *);
int displayHelp(info_t *);

/* toem_builtin1.c */
int displayHistory(info_t *);
int manageAlias(info_t *);

/*toem_getline.c */
ssize_t getInput(info_t *);
int getLine(info_t *, char **, size_t *);
void handleSigint(int);

/* toem_getinfo.c */
void initializeInfo(info_t *);
void setShellInfo(info_t *, char **);
void freeShellInfo(info_t *, int);

/* toem_environ.c */
char *getEnvironmentVariable(info_t *, const char *);
int executeEnvironmentCommand(info_t *);
int setEnvironmentVariable(info_t *);
int unsetEnvironmentVariable(info_t *);
int populateEnvironmentList(info_t *);

/* toem_getenv.c */
char **getEnvironment(info_t *);
int unsetEnvironmentVariable(info_t *, char *);
int setEnvironmentVariable(info_t *, char *, char *);

/* toem_history.c */
char *getHistoryFile(info_t *info);
int writeHistory(info_t *info);
int readHistory(info_t *info);
int buildHistoryList(info_t *info, char *buf, int linecount);
int renumberHistory(info_t *info);

/* toem_lists.c */
list_t *addNode(list_t **, const char *, int);
list_t *addNodeEnd(list_t **, const char *, int);
size_t printListString(const list_t *);
int deleteNodeAtIndex(list_t **, unsigned int);
void freeList(list_t **);

/* toem_lists1.c */
size_t getListLength(const list_t *);
char **listToStrings(list_t *);
size_t printList(const list_t *);
list_t *nodeStartsWith(list_t *, char *, char);
ssize_t getNodeIndex(list_t *, list_t *);

/* toem_vars.c */
int isChainDelimiter(info_t *, char *, size_t *);
void checkChain(info_t *, char *, size_t *, size_t, size_t);
int replaceAliases(info_t *);
int replaceVariables(info_t *);
int replaceString(char **, char *);
#endif

