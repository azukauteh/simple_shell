#include "shell.h"

ssize_t get_new_len(char *line);


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
int i = 0;
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


