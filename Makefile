# Define compiler and compiler flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Define source files and their corresponding object files
SOURCES = main.c getLine.c parser.c builtin.c environ.c shell_loop.c vars.c \
          memory.c lists.c string.c tokenizer.c getinfo.c getenv.c errors.c \
          history.c realloc.c
OBJECTS = $(SOURCES:.c=.o)

# Define the name of the output executable
EXECUTABLE = myshell

# Default target
all: $(EXECUTABLE)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create the executable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

# Clean target to remove object files and the executable
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

