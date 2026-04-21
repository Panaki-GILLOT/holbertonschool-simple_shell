#include "shell.h"

/**
 * print_error - prints a not found error to stderr
 * @av0: name of the shell
 * @line_count: current line number
 * @cmd: command that was not found
 *
 * Return: void
 */
static void print_error(char *av0, int line_count, char *cmd)
{
	char num[12];
	int i = 0;
	int tmp;

	tmp = line_count;
	if (tmp == 0)
		num[i++] = '0';
	while (tmp > 0)
	{
		num[i++] = '0' + (tmp % 10);
		tmp /= 10;
	}
	num[i] = '\0';
	write(STDERR_FILENO, av0, strlen(av0));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, num, strlen(num));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, cmd, strlen(cmd));
	write(STDERR_FILENO, ": not found\n", 12);
}

/**
 * execute_command - forks and executes a command
 * @args: argument array for execve
 * @path: full path to the executable
 * @env: environment variables array
 * @av0: name of the shell for error messages
 * @line_count: current line number for error messages
 * @line: input line buffer
 *
 * Return: void
 */
void execute_command(char **args, char *path, char **env,
		char *av0, int line_count, char *line)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		write(STDERR_FILENO, "fork error\n", 11);
		return;
	}
	if (pid == 0)
	{
		if (execve(path, args, env) == -1)
		{
			print_error(av0, line_count, args[0]);
			free(path);
			free(args);
			free(line);
			_exit(127);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}
