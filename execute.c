#include "shell.h"

/**
 * execute_command - forks and executes a command
 * @args: argument array for execve
 * @path: full path to the executable
 * @env: environment variables array
 * @av0: name of the shell (argv[0])
 * @line_count: current line number for error messages
 * @line: input line buffer (freed on execve failure)
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
		perror("fork");
		return;
	}
	if (pid == 0)
	{
		if (execve(path, args, env) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
				av0, line_count, args[0]);
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
