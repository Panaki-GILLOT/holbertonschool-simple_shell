#include "shell.h"

/**
 * find_path - searches for a command in PATH directories
 * @command: command name to locate
 * @env: environment variables array
 *
 * Description: builds full path for a command by iterating
 * through PATH directories and checking execution permission.
 *
 * Return: full path to command if found, NULL otherwise
 */
char *find_path(char *command, char **env)
{
	char *path = NULL;
	char *path_copy;
	char *dir;
	char *full_path;
	int i = 0;

	if (!command || !env)
		return (NULL);

	/* If command contains '/', use it directly */
	if (strchr(command, '/'))
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}

	/* Find PATH in environment */
	while (env[i])
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
		{
			path = env[i] + 5;
			break;
		}
		i++;
	}

	if (!path || *path == '\0')
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		full_path = malloc(strlen(dir) + strlen(command) + 2);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
