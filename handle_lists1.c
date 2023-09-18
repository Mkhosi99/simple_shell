#include "shell.h"

/**
 * lenth_of_list - function will find length of linked list
 * @top: points to the first node
 * Return: size of the list should be returned
 */
size_t lenth_of_list(const list_sh *top)
{
	size_t x = 0;

	while (top)
	{
		top = top->nextNode;
		x++;
	}
	return (x);
}

/**
 * convert_list_to_strings - function will return array of strings
 *                           of list->string
 * @top: points to the first node
 * Return: array of strings should be returned
 */
char **convert_list_to_strings(list_sh *top)
{
	list_sh *nde = top;
	size_t x = lenth_of_list(top), m;
	char **strings;
	char *strng;

	if (!top || !x)
		return (NULL);
	strings = malloc(sizeof(char *) * (x + 1));

	if (!strings)
		return (NULL);
	for (x = 0; nde; nde = nde->nextNode, x++)
	{
		strng = malloc(the_string_lenth(nde->string) + 1);
		if (!strng)
		{
			for (m = 0; m < x; m++)
				free(strings[m]);
			free(strings);
			return (NULL);
		}

		strng = copy_the_string(strng, nde->string);
		strings[x] = strng;
	}
	strings[x] = NULL;
	return (strings);
}

/**
 * output_list - function will print all the elements of list_sh list
 * @top: points to first node
 * Return: size of the list should be returned
 */
size_t output_list(const list_sh *top)
{
	size_t x = 0;

	while (top)
	{
		put_string(transform_number(top->int_num, 10, 0));
		put_character(':');
		put_character(' ');
		put_string(top->string ? top->string : "(nil)");
		put_string("\n");
		top = top->nextNode;
		x++;
	}
	return (x);
}

/**
 * node_starting - function returns node of string starting with prefix
 * @nde: points to head of list
 * @prfx: the matching string
 * @a: indicates next char after matching prefix
 * Return: matching node to be returned or null
 */
list_sh *node_starting(list_sh *nde, char *prfx, char a)
{
	char *b = NULL;

	while (nde)
	{
		b = begins_with(nde->string, prfx);
		if (b && ((a == -1) || (*b == a)))
			return (nde);
		nde = nde->nextNode;
	}
	return (NULL);
}

/**
 * fetch_node_indicator - function will get index of a node
 * @top: points to head of list
 * @nde: points to the node
 * Return: will return index of node or -1
 */
ssize_t fetch_node_indicator(list_sh *top, list_sh *nde)
{
	size_t x = 0;

	while (top)
	{
		if (top == nde)
			return (x);
		top = top->nextNode;
		x++;
	}
	return (-1);
}
