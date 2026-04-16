#include "shell.h"

/**
 * main - simple shell entry point
 * @ac: argument count
 * @av: argument vector
 * @env: environment variables
 *
 * Description: reads user input, executes commands using PATH,
 * handles builtins (exit, env), and manages child processes.
 * Prints error messages matching /bin/sh format.
 *
 * Return: 0 on success
 */
int main(int ac, char **av, char **env)
{
	char *line = NULL;
	size_t len = 0;
	char **args;
	char *path;
	pid_t pid;
	int status;
	int line_count = 0;
	int i;

	(void)ac;

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

		args = split_line(line);
		if (!args || !args[0])
		{
			free(args);
			continue;
		}

		/* BUILTIN: exit */
		if (strcmp(args[0], "exit") == 0)
		{
			free(args);
			free(line);
			exit(0);
		}

		/* BUILTIN: env */
		if (strcmp(args[0], "env") == 0)
		{
			for (i = 0; env[i]; i++)
				printf("%s\n", env[i]);
			free(args);
			continue;
		}

		/* PATH resolution */
		path = find_path(args[0], env);

		/* Command not found: print error before fork */
		if (!path)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
				av[0], line_count, args[0]);
			free(args);
			continue;
		}

		/* Fork and execute */
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			free(path);
			free(args);
			continue;
		}

		if (pid == 0)
		{
			/* Child process */
			if (execve(path, args, env) == -1)
			{
				fprintf(stderr, "%s: %d: %s: not found\n",
					av[0], line_count, args[0]);
				free(path);
				free(args);
				free(line);
				_exit(127);
			}
		}
		else
		{
			/* Parent process */
			waitpid(pid, &status, 0);
		}

		free(path);
		free(args);
	}

	free(line);
	return (0);
}
