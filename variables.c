#include "shell.h"

/**
 * the_chain - function tests if a chain is a chain delimeter
 * @data: the param structure
 * @bufr: indicates the character
 * @post: the present position address in the buffer
 * Return: will return 1 if it is chain delimeter or will be 0 if not
 */
int the_chain(data_sh *data, char *bufr, size_t *post)
{
	size_t x = *post;

	if (bufr[x] == '|' && bufr[x + 1] == '|')
	{
		bufr[x] = 0;
		x++;
		data->buffer_type_command = COMMAND_OR;
	}
	else if (bufr[x] == '&' && bufr[x + 1] == '&')
	{
		bufr[x] = 0;
		x++;
		data->buffer_type_command = COMMAND_AND;
	}
	else if (bufr[x] == ';')
	{
		bufr[x] = 0;
		data->buffer_type_command = COMMAND_CHAIN;
	}
	else
		return (0);
	*post = x;
	return (1);
}

/**
 * look_at_chain - function assesses if chaining should be continued
 * @data: indicates the param structure
 * @bfr: this indicates the character buffer
 * @ps: the present position address in the buffer
 * @st: indicates what will be the start position in buffer
 * @ln: indicates what will be the length of the buffer
 * Return: should return void
 */
void look_at_chain(data_sh *data, char *bfr, size_t *ps, size_t st, size_t ln)
{
	size_t x = *ps;

	if (data->buffer_type_command == COMMAND_AND)
	{
		if (data->condition)
		{
			bfr[st] = 0;
			x = ln;
		}
	}
	if (data->buffer_type_command == COMMAND_OR)
	{
		if (data->condition)
		{
			bfr[st] = 0;
			x = ln;
		}
	}

	*ps = x;
}

/**
 * restore_otherwise - function will replace an alias in tokenized string
 * @data: indicates what will be the param structure
 * Return: will return 1 if it is replaced or 0 if not
 */
int restore_otherwise(data_sh *data)
{
	int x;
	list_sh *nde;
	char *post;

	for (x = 0; x < 10; x++)
	{
		nde = node_starting(data->otherwise, data->argvec[0], '=');
		if (!nde)
			return (0);
		free(data->argvec[0]);
		post = the_string_character(nde->string, '=');
		if (!post)
			return (0);
		data->argvec[0] = post;
	}
	return (1);
}

/**
 * restore_variables - function will replace variables in a tokenized string
 * @data: this indicates the param structure in function
 * Return: 1 will be returned if variables is replaced and 0 if not
 */
int restore_variables(data_sh *data)
{
	int x = 0;
	list_sh *nde;

	for (x = 0; data->argvec[x]; x++)
	{
		if (data->argvec[x][0] != '$' || !data->argvec[x][1])
			continue;

		if (!the_string_compare(data->argvec[x], "$?"))
		{
			restore_string(&(data->argvec[x]),
					duplicate_the_string(transform_number(data->condition, 10, 0)));
			continue;
		}
		if (!the_string_compare(data->argvec[x], "$$"))
		{
			restore_string(&(data->argvec[x]),
					duplicate_the_string(transform_number(getpid(), 10, 0)));
			continue;
		}
		nde = node_starting(data->envir, &data->argvec[x][1], '=');
		if (nde)
		{
			restore_string(&(data->argvec[x]),
					duplicate_the_string(the_string_character(nde->string, '=') + 1));
			continue;
		}
		restore_string(&data->argvec[x], duplicate_the_string(""));
	}
	return (0);
}

/**
 * restore_string - function will replace a string
 * @prev: indicates the address of the old or previous string
 * @fresh: indicates the new string
 * Return: will return 1 if it is replaced and 0 if not
 */
int restore_string(char **prev, char *fresh)
{
	free(*prev);
	*prev = fresh;
	return (1);
}
