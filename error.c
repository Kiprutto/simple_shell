#include"shell.h"
/**
 * br_puterror - Prints an error message to the standard error stream
 * @err: The error message to print
 *
 * Return: Void
 */
void br_puterror(char *err)
{
	size_t len;
	ssize_t num_written;

	len = br_strlen(err);
	num_written = write(STDERR_FILENO, err, len);
	if (num_written == -1)
	{
		perror("write");
	}
}
