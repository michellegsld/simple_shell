#include "shell.h"
/**
 * _getline - retrieve command line
 * @line: buffer to store command line
 * @size: length of command line
 *
 * Return: Number of lines read on success or -1 on fail
 */
ssize_t _getline(char **line, size_t *line_size)
{
	ssize_t read_cnt, read_total = 0;
	size_t offset = 0; /* line offset for each iteration */
	char *buffer = NULL;

	buffer = alloc_mngr(buffer, (sizeof(char) * 1024));

	if (!buffer) /* error if malloc fail */
	{
		perror("Allocation failed");
		return (-1);
	}

	/* read stdin to dynamic buffer */
	while ((read_cnt = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0)
	{
		if (read_cnt == -1) /* check for read failure */
			return (-1);

		if (read_cnt) /* if new text read */
		{
			read_total += read_cnt; /* add num of bytes last read to total */

			/* reallocate line to receive new text */
			*line = alloc_mngr(*line, (sizeof(char) * read_total));
			if (!(*line)) /* check for reallocation fail */
			{
				perror("Reallocation failed");
				return (-1);
			}

			/* copy buffer to line from current offset */
			_strncpy(((*line) + offset), buffer, read_cnt);

			offset = read_total; /* advance line offset */
		}
		if ((*line)[offset - 1] == '\n') /* if line is \n terminated */
			break; /* break read loop */
	}
	(*line)[offset - 1] = '\0'; /* null-terminate line */

	/* return total number of bytes read */
	return (*line_size = offset);
}