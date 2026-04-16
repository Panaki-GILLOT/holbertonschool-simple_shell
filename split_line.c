#include "shell.h"

/**
 * split_line - splits a string into arguments
 * @line: input string from getline
 *
 * Description: tokenizes input using spaces and tabs
 * to create argv-style array for execve.
 *
 * Return: array of strings (arguments), NULL on failure
 */
char **split_line(char *line)
{
	char **args;
	char *token;
	int i = 0;

	if (!line)
		return (NULL);

	args = malloc(sizeof(char *) * 1024);
	if (!args)
		return (NULL);

	token = strtok(line, " \t\n");
	while (token)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;

	return (args);
}
