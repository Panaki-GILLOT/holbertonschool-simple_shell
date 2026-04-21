#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Core functions */
char **split_line(char *line);

char *find_path(char *command, char **env);

/* Builtins */
int builtin_env(char **env);

int builtin_exit(char **args, char *line);

/* Execution */
void execute_command(char **args, char *path, char **env,

	char *av0, int line_count, char *line);

#endif /* SHELL_H */
