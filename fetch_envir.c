#include "shell.h"

/**
 * fetch_envir - Function informs of string copy environment
 * @data: Function parameter with likely arguments
 *
 * Return: return will always be zero
 */
char **fetch_envir(data_sh *data)
{
	if (!data->envirnmnt || data->alter_environ)
	{
		data->envirnmnt = convert_list_to_strings(data->envir);
		data->alter_environ = 0;
	}

	return (data->envirnmnt);
}

/**
 * unset_envir - Function removes envirmnt variable
 * @data: Parameter structure with arguments
 * @param: Indicates string environment and the variable property
 * Return: 1 is returned if deleted and zero if otherwise
 */
int unset_envir(data_sh *data, char *param)
{
	list_sh *nde = data->envir;
	size_t x = 0;
	char *a;

	if (!nde || !param)
		return (0);

	while (nde)
	{
		a = begins_with(nde->string, param);
		if (a && *a == '=')
		{
			data->alter_environ = remove_node_at_indicator(&(data->envir), x);
			x = 0;
			nde = data->envir;
			continue;
		}
		nde = nde->nextNode;
		x++;
	}
	return (data->alter_environ);
}

/**
 * set_envir - Function creates new environment variable
 * @data: Parameter with likely arguments,
 *        will be used for constant prototype function
 * @param: Indicates the environment and the variable property
 * @worth: Indicates the string environments variable value
 * Return: will always return zero
 */
int set_envir(data_sh *data, char *param, char *worth)
{
	char *bufr = NULL;
	list_sh *nde;
	char *pter;

	if (!param || !worth)
		return (0);

	bufr = malloc(the_string_lenth(param) + the_string_lenth(worth) + 2);
	if (!bufr)
		return (1);
	copy_the_string(bufr, param);
	concatenate_the_strings(bufr, "=");
	concatenate_the_strings(bufr, worth);
	nde = data->envir;
	while (nde)
	{
		pter = begins_with(nde->string, param);
		if (pter && *pter == '=')
		{
			free(nde->string);
			nde->string = bufr;
			data->alter_environ = 1;
			return (0);
		}
		nde = nde->nextNode;
	}
	attach_node_at_end(&(data->envir), bufr, 0);
	free(bufr);
	data->alter_environ = 1;
	return (0);
}
