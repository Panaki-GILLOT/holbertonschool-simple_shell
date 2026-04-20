#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * shell.h - header file for simple shell project
 *
 * Description: contains function prototypes, builtins and
 * standard libraries used by the simple shell program.
 */
char **split_line(char *line);
char *find_path(char *command, char **env);
int builtin_env(char **env);
int builtin_exit(char **args, char *line);
void execute_command(char **args, char *path, char **env,
	char *av0, int line_count, char *line);

#endif /* SHELL_H */
