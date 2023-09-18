#include "shell.h"

/**
 * the_hist - the function lists history, from 0
 * @data: The possible arguments passed
 *
 * Return: returns zero always
 */
int the_hist(data_sh *data)
{
	output_list(data->histo_node);
	return (0);
}

/**
 * undo_alias - Function makes an alias into a string
 * @data: The parameter of the struct
 * @strng: Indicates the string
 *
 * Return: Will be 0 is successful and 1 if error
 */
int undo_alias(data_sh *data, char *strng)
{
	char *a, b;
	int remit;

	a = the_string_character(strng, '=');
	if (!a)
		return (1);
	b = *a;
	*a = 0;
	remit = remove_node_at_indicator(&(data->otherwise),
			fetch_node_indicator(data->otherwise, 
				node_starting(data->otherwise, strng, -1)));
	*a = b;
	return (remit);
}

/**
 * make_alias - function sets an alias to a string
 * @data: indicates the param
 * @strng: indicates string alias
 * Return: should always return 0 if working and 1 if not
 */
int make_alias(data_sh *data, char *strng)
{
	char *a;

	a = the_string_character(strng, '=');
	if (!a)
		return (1);
	if (!*++a)
		return (undo_alias(data, strng));

	undo_alias(data, strng);
	return (attach_node_at_end(&(data->otherwise), strng, 0) == NULL);
}

/**
 * outpt_alias - function will print alias string
 * @nde: indicates alias node
 * Return: 0 if working and 1 if not
 */
int outpt_alias(list_sh *nde)
{
	char *a = NULL, *b = NULL;

	if (nde)
	{
		a = the_string_character(nde->string, '=');
		for (b = nde->string; b <= a; b++)
			put_character(*b);
			put_character('\'');
			put_string(a + 1);
			put_string("'\n");
			return (0);
	}
}

/**
 * custm_alias - function mimics builtin alias
 * @data: param with likely arguments
 * Return: should return 0
 */
int custm_alias(data_sh *data)
{
	int x = 0;
	char *a = NULL;
	list_sh *nde = NULL;

	if (data->argcount == 1)
	{
		nde = data->otherwise;
		while (nde)
		{
			outpt_alias(nde);
			nde = nde->nextNode;
		}
		return (0);
	}
	for (x = 1; data->argvec[x]; x++)
	{
		a = the_string_character(data->argvec[x], '=');
		if (a)
			make_alias(data, data->argvec[x]);
		else
			outpt_alias(node_starting(data->otherwise, data->argvec[x], '='));
	}

	return (0);
}
