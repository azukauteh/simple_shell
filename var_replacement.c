#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE 80
/**
 * replace_var - function to replace variable
 * @in: pointer
 * Return: 0
 */
void replace_var(char *in)
{
	char *out = malloc(MAX_LINE);
	int i = 0, j = 0;

	while (in[i] != '\0')
	{
		if (in[i] == '$')
		{	i++;
			if (in[i] == '$')
			{	out[j] = '$';
				j++;
			}
			else
			{
				char *var_name = malloc(MAX_LINE);
				int k = 0;

				while (in[i] != '\0' && in[i] != ' ')
				{	var_name[k] = in[i];
					i++;
					k++;
				}
				var_name[k] = '\0';
				char *var_value = getenv(var_name);

				if (var_value != NULL)
				{	write(STDOUT_FILENO, var_value, strlen(var_value));
					j += strlen(var_value);
				}
				free(var_name);
			}
		}
		else
		{	out[j] = in[i];
			i++;
			j++;
		}
	}
	out[j] = '\0';
	strcpy(in, out);
	free(out);
}
/**
 * main - function
 * @void: parameter
 * Return: 0
 */
int main(void)
{
	char in[MAX_LINE];

	fgets(in, MAX_LINE, stdin);
	replace_var(in);
	write(STDOUT_FILENO, in, strlen(in));
	return (0);
}
