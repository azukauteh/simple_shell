#include "shell.h"

/**
 * l_length - function that calc length
 * @h: pointer
 * Return: list size
 */
size_t l_length(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * l_str - function that will return string array
 * @head: pointer
 * Return: string array
 */
char **l_str(list_t *head)
{
	list_t *node = head;
	size_t i = l_length(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * _plist - Function display element of list_t linked list
 * @h: pointer
 * Return: list size
 */
size_t _plist(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(conv_num(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * _snode - function to return node
 * @node: pointer
 * @prefix: string
 * @c: character
 * Return: exact node otherwise null
 */
list_t *_snode(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * getn_ind - Function that fetches index of node
 * @head: pointer
 * @node: pointer
 * Return: index node otherwise -1
 */
ssize_t getn_ind(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
