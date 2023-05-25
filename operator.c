#include "shell.h"

void handle_line(char **line, ssize_t read);
ssize_t get_new_len(char *line);
void logical_ops(char *line, ssize_t *new_len);

/**
 * handle_line - Partitions a line read from standard input as needed.
 * @line: A pointer to a line read from standard input.
 * @read: The length of line.
 *
 * Description: Spaces are inserted to separate ";", "||", and "&&".
 *              Replaces "#" with '\0'.
 */

void handle_line(char **line, ssize_t read)
{
char *new_line = malloc(read);
int j = 0;
int i = 0;

if (!new_line)
return;

/*for (size_t i = 0; (*line)[i]; i++)*/
for (i = 0; (*line)[i]; i++)
{
char current = (*line)[i];
char next = (*line)[i + 1];
if (i != 0)
{
char previous = (*line)[i - 1];
if (current == ';' || current == '&' || current == '|')
{
if ((current == ';' && next == ';') ||
(current == '&' && next == '&') ||
(current == '|' && next == '|'))
{
if (previous != ' ' && previous != current)
new_line[j++] = ' ';
new_line[j++] = current;
continue;
}
else if ((current == ';' && previous == ';') ||
(current == '&' && next != ' ') ||
(current == '|' && next != ' '))
{
new_line[j++] = current;
new_line[j++] = ' ';
continue;
}
if (previous != ' ')
new_line[j++] = ' ';
new_line[j++] = current;
if (next != ' ')
new_line[j++] = ' ';
continue;
}
}
else if (current == ';')
{
if (i != 0 && (*line)[i - 1] != ' ')
new_line[j++] = ' ';
new_line[j++] = current;
if (next != ' ' && next != ';')
new_line[j++] = ' ';
continue;
}
new_line[j++] = current;
}
new_line[j] = '\0';
free(*line);
*line = new_line;
}


/**
 * logical_ops - Checks a line for logical operators "||" or "&&".
 * @line: A pointer to the character to check in the line.
 * @new_len: Pointer to new_len in get_new_len function.
 */

void logical_ops(char *line, ssize_t *new_len)
{
char previous, current, next;
previous = *(line - 1);
current = *line;
next = *(line + 1);
if (current == '&')
{
if (next == '&' && previous != ' ')
(*new_len)++;
else if (previous == '&' && next != ' ')
(*new_len)++;
}
else if (current == '|')
{
if (next == '|' && previous != ' ')
(*new_len)++;
else if (previous == '|' && next != ' ')
(*new_len)++;
}
}
