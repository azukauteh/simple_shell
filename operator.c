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
 * get_new_len - Gets the new length of a line partitioned
 *               by ";", "||", "&&&", or "#".
 * @line: The line to check.
 *
 * Return: The new length of the line.
 *
 * Description: Cuts short lines containing '#' comments with '\0'.
 */

ssize_t get_new_len(char *line)
{
ssize_t new_len = 0;
char current, next;
int i =0;
/*for (i = 0; (*line)[i]; i++)*/
for (i = 0; line[i]; i++)
{
current = line[i];
next = line[i + 1];
if (current == '#')
{
if (i == 0 || line[i - 1] == ' ')
{
line[i] = '\0';
break;
}
}
else if (i != 0)
{
if (current == ';' || current == '&' || current == '|')
{
if (((current == ';' || current == '&') && next == ';') ||
(current == '|' && next == '|'))
{
if (line[i - 1] != ' ' && line[i - 1] != current)
new_len += 2;
continue;
}
else if (((current == ';' || current == '&') && line[i - 1] == ';') ||
(current == '|' && next != ' '))
{
new_len += 2;
continue;
}
if (line[i - 1] != ' ')
new_len++;
if (next != ' ')
new_len++;
}
}
else if (current == ';')
{
if (i != 0 && line[i - 1] != ' ')
new_len++;
if (next != ' ' && next != ';')
new_len++;
}
new_len++;
}
return (new_len);
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
