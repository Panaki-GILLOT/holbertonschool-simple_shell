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
 * _putstr - writes a string to a file descriptor
 * @str: string to write
 * @fd: file descriptor
 *
 * Return: void
 */
static void _putstr(char *str, int fd)
{
	while (*str)
	{
		write(fd, str, 1);
		str++;
	}
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
		_putstr(env[i], STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	return (0);
}
