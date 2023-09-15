#include "shell.h"

/**
 * attach_node - function adds node at the start of list
 * @top: points to the head of node
 * @strng: indicates the string field mode
 * @numbr: indicates the node index used by histo_node
 * Return: should return the size of the list
 */
list_sh *attach_node(list_sh **top, const char *strng, int numbr)
{
	list_sh *new_top;

	if (!top)
		return (NULL);
	new_top = malloc(sizeof(list_sh));
	if (!new_top)
		return (NULL);
	set_block_memory((void *)new_top, 0, sizeof(list_sh));
	new_top->int_num = numbr;
	if (strng)
	{
		new_top->string = duplicate_the_string(strng);
		if (!new_top->string)
		{
			free(new_top);
			return (NULL);
		}
	}
	new_top->nextNode = *top;
	*top = new_top;
	return (new_top);
}

/**
 * attach_node_at_end - function puts node at end of list
 * @top: points to the head of node
 * @strng: indicates the string field node
 * @numbr: indicates the node index used by histo_node
 * Return: should return size of the list
 */
list_sh *attach_node_at_end(list_sh **top, const char *strng, int numbr)
{
	list_sh *newNde, *nde;

	if (!top)
		return (NULL);

	nde = *top;
	newNde = malloc(sizeof(list_sh));
	if (!newNde)
		return (NULL);
	set_block_memory((void *)newNde, 0, sizeof(list_sh));
	newNde->int_num = numbr;
	if (strng)
	{
		newNde->string = duplicate_the_string(strng);
		if (!newNde->string)
		{
			free(newNde);
			return (NULL);
		}
	}
	if (nde)
	{
		while (nde->nextNode)
			nde = nde->nextNode;
		nde->nextNode = newNde;
	}
	else
		*top = newNde;
	return (newNde);
}

/**
 * output_list_string - function prints only string element of list_sh list
 * @top: pointer to first node
 * Return: should return size of the list
 */
size_t output_list_string(const list_sh *top)
{
	size_t x = 0;

	while (top)
	{
		put_string(top->string ? top->string : "(nil)");
		put_string("\n");
		top = top->nextNode;
		x++;
	}
	return (x);
}

/**
 * remove_node_at_indicator - function deletes a node at given time
 * @top: pointer to the first node in list
 * @indx: indicates the index of the node to remove
 * Return: 1 if working and 0 if not
 */
int remove_node_at_indicator(list_sh **top, unsigned int indx)
{
	list_sh *nde, *befreNde; /* previous node */
	unsigned int x = 0;

	if (!top || !*top)
		return (0);

	if (!indx)
	{
		nde = *top;
		*top = (*top)->nextNode;
		free(nde->string);
		free(nde);
		return (1);
	}
	nde = *top;
	while (nde)
	{
		if (x == indx)
		{
			befreNde->nextNode = nde->nextNode;
			free(nde->string);
			free(nde);
			return (1);
		}
		x++;
		befreNde = nde;
		nde = nde->nextNode;
	}
	return (0);
}

/**
 * frees_the_list - function frees all the nodes in a list
 * @top: points to head node
 * Return: should return void
 */
void frees_the_list(list_sh **top)
{
	list_sh *nde, *nxtNde, *hd; /* hd == head */

	if (!top || !*top)
		return;
	hd = *top;
	nde = hd;
	while (nde)
	{
		nxtNde = nde->nextNode;
		free(nde->string);
		free(nde);
		nde = nxtNde;
	}
}
