#include "shell.h"

/**
 * builtin_exit - exits the shell
 * @args: argument array (unused)
 * @line: input line to free before exit
 *
 * Return: does not return
 */
int builtin_exit(char **args, char *line)
{
	free(args);
	free(line);
	exit(0);
}

/**
 * builtin_env - prints the current environment
 * @env: environment variables array
 *
 * Return: 0 on success
 */
int builtin_env(char **env)
{
	int i = 0;

	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
