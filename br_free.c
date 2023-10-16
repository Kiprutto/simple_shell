#include "shell.h"
static char *last_input;
/**
 * free_tokens - frees memory allocated dynamically by tokenize()
 * @ptr: pointer to allocated memory
 * Return: void.
 */
void free_tokens(char **ptr)
{
	int i;

	for (i = 0; ptr[i]; i++)
		free((ptr[i]));
	free(ptr);
}

/**
 * free_last_input - frees the last user input
 **/
void free_last_input(void)
{
	free(last_input);
	last_input = NULL;
}

/**
 * free_path - Frees the global variable containing the PATH environment
 * variable value
 * Return: Nothing
 */
void free_path(void)
{
	if (environ != NULL)
	{
		size_t i = 0;

		while (environ[i] != NULL)
		{
			if (br_strncmp(environ[i], "PATH=", 5) == 0)
			{
				free(environ[i]);
				environ[i] = NULL;
				break;
			}
			i++;
		}
	}
}
