#include "shell.h"

/**
 * the_envir - Functions outputs environment
 * @data: Variable with likely arguments,
 *        Will be used to maintain constant function prototype
 * Return: Will always be zero
 */
int the_envir(data_sh *data)
{
	output_list_string(data->envir);
	return (0);
}

/**
 * get_envir - Collects the value of a environment variable
 * @data: Variable with the likely arguments
 * @id: The environmental variable name
 *
 * Return: returns the value
 */
char *get_envir(data_sh *data, const char *id)
{
	list_sh *nde = data->envir;
	char *a;

	while (nde)
	{
		a = begins_with(nde->string, id);
		if (a && *a)
			return (a);
		nde = nde->nextNode;
	}
	return (NULL);
}

/**
 * the_set_envir - Function will initialize a new environment variable,
 *                 or it alter the existing one
 * @data: Variable with the likely arguments,
 *        will be used to maintain to constan function prototype
 *
 * Return: returns zero always
 */
int the_set_envir(data_sh *data)
{
	if (data->argcount != 3)
	{
		_puts_e("Invalid number of arguments\n");
		return (1);
	}
	if (set_envir(data, data->argvec[1], data->argvec[2]))
		return (0);
	return (1);
}

/**
 * the_unset_envir - Function removes an environment variable
 * @data: Variable with likely arguments, and will be used
 *        to maintain a constant function prototype
 * Return: returns zero always
 */
int the_unset_envir(data_sh *data)
{
	int x;

	if (data->argcount == 1)
	{
		_puts_e("Not enough arguments\n");
		return (1);
	}
	for (x = 1; x <= data->argcount; x++)
		unset_envir(data, data->argvec[x]);

	return (0);
}

/**
 * occupy_envir_list - Function makes and fills environment linked list
 * @data: Variable with likely arguments and
 *       is used to maintain a constant function prototype
 * Return: returns zero always
 */
int occupy_envir_list(data_sh *data)
{
	list_sh *nde = NULL;
	size_t x;

	for (x = 0; envirnmnt[x]; x++)
		attach_node_at_end(&nde, envirnmnt[x], 0);
	data->envir = nde;
	return (0);
}
