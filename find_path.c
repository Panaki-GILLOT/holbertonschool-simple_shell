#include "shell.h"

/**
 * get_path_env - retrieves PATH value from environment
 * @env: environment variables array
 *
 * Return: pointer to PATH value, NULL if not found
 */
static char *get_path_env(char **env)
{
	int i = 0;

	while (env[i])
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

/**
 * search_in_path - searches command in each PATH directory
 * @command: command name to locate
 * @path: PATH value string
 *
 * Return: full path if found, NULL otherwise
 */
static char *search_in_path(char *command, char *path)
{
	char *path_copy;
	char *dir;
	char *full_path;

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
	char *path;

	if (!command || !env)
		return (NULL);
	if (strchr(command, '/'))
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}
	path = get_path_env(env);
	if (!path || *path == '\0')
		return (NULL);
	return (search_in_path(command, path));
}
