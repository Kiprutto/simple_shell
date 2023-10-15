#include "shell.h"
static char *last_input;
/**
 * get_input - Read the line of input from the user.
 * Return: Pointer to a buffer containing the user's input.
 */
char *get_input(void)
{
	/*char *previous_input;*/
	char *input = NULL;
	size_t input_size = 0;
	ssize_t read_result;

	do {
		prompt();
		read_result = getline(&input, &input_size, stdin);
		if (read_result == -1)
		{
			free(input);
			/*br_puts("\n");*/
			return (NULL);
		}
		input[read_result - 1] = '\0';
	} while (input[0] == '\0' || isspace(input[0]));
	last_input = input;
	return (input);
}

/**
 * tokenize - splits an array string into tokens using a delimiter.
 * @str: the string to be tokenized.
 * @delim: the delimiter used to split the string.
 * Return: an array of pointers to the tokens.
 */
char **tokenize(char *str, const char *delim)
{
	char *token = NULL;
	char **ret = NULL;
	int i = 0;

	token = strtok(str, delim);
	while (token)
	{
		ret = realloc(ret, sizeof(char *) * (i + 1));
		if (ret == NULL)
			return (NULL);

		ret[i] = malloc(br_strlen(token) + 1);
		if (!(ret[i]))
			return (NULL);

		br_strcpy(ret[i], token);
		token = strtok(NULL, delim);
		i++;
	}
	ret = realloc(ret, (i + 1) * sizeof(char *));
	if (!ret)
		return (NULL);

	ret[i] = NULL;
	return (ret);
}

/**
 * tokenize_input - splits a user input string into tokens
 * @input: the user input string to be tokenized
 * Return: an array of pointers to the tokens, or NULL if an error occurs
 */
char **tokenize_input(char *input)
{
	char **tokens = NULL;
	char *input_copy = NULL;

	input_copy = br_strdup(input);
	if (input_copy == NULL)
	{
		br_puts("Malloc error");
		exit(EXIT_FAILURE);
	}
	tokens = tokenize(input_copy, " \t\r\n\a");
	free(input_copy);
	return (tokens);
}

/**
 * get_line - Read input from the standard input.
 * Return: The string enter by the user.
*/
void *get_line(void)
{
	static char buffer[BUFFER_SIZE];
	static int buf_pos, buf_size;
	char *input_str = NULL;
	char current_char;
	int input_len = 0;

	while (1)
	{
		if (buf_pos >= buf_size)
		{
			buf_size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			buf_pos = 0;
			if (buf_size == 0)
				return (input_str);
			else if (buf_size < 0)
			{
				perror("read");
				return (NULL);
			}
		}

		current_char = buffer[buf_pos];

		buf_pos++;

		if (current_char == '\n')
		{
			input_str = realloc(input_str, input_len + 1);
			input_str[input_len] = '\0';
			return (input_str);
		}
		else
		{
			input_str = realloc(input_str, input_len + 1);
			input_str[input_len] = current_char;
			input_len++;
		}
	}
}

