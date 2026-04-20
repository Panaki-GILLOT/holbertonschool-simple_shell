#include "shell.h"

/**
 * handle_builtins - checks and executes builtin commands
 * @args: argument array
 * @line: input line buffer
 * @env: environment variables array
 *
 * Return: 1 if builtin was handled, 0 otherwise
 */
static int handle_builtins(char **args, char *line, char **env)
{
	if (strcmp(args[0], "exit") == 0)
		builtin_exit(args, line);
	if (strcmp(args[0], "env") == 0)
	{
		builtin_env(env);
		return (1);
	}
	return (0);
}

/**
 * print_not_found - prints command not found error to stderr
 * @av0: shell name
 * @line_count: current line number
 * @cmd: command not found
 *
 * Return: void
 */
static void print_not_found(char *av0, int line_count, char *cmd)
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
 * process_line - parses and executes one input line
 * @line: input string to process
 * @av: shell argument vector
 * @env: environment variables array
 * @line_count: current line number
 *
 * Return: void
 */
static void process_line(char *line, char **av, char **env, int line_count)
{
	char **args;
	char *path;

	args = split_line(line);
	if (!args || !args[0])
	{
		free(args);
		return;
	}
	if (handle_builtins(args, line, env))
	{
		free(args);
		return;
	}
	path = find_path(args[0], env);
	if (!path)
	{
		print_not_found(av[0], line_count, args[0]);
		free(args);
		return;
	}
	execute_command(args, path, env, av[0], line_count, line);
	free(path);
	free(args);
}

/**
 * run_shell - main shell loop
 * @av: argument vector of the shell process
 * @env: environment variables array
 *
 * Return: 0 on success
 */
static int run_shell(char **av, char **env)
{
	char *line = NULL;
	size_t len = 0;
	int line_count = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 4);
		if (getline(&line, &len, stdin) == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			return (0);
		}
		line_count++;
		line[strcspn(line, "\n")] = '\0';
		process_line(line, av, env, line_count);
	}
	free(line);
	return (0);
}

/**
 * main - simple shell entry point
 * @ac: argument count
 * @av: argument vector
 * @env: environment variables
 *
 * Return: 0 on success
 */
int main(int ac, char **av, char **env)
{
	(void)ac;
	return (run_shell(av, env));
}
