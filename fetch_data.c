#include "shell.h"

/**
 * erase_data - Fuction creates and initializes data_sh structure
 * @data: The data_sh structure address
 */
void erase_data(data_sh *data)
{
	data->argument = NULL;
	data->argvec = NULL;
	data->trail = NULL;
	data->argcount = 0;
}

/**
 * set_data - Function initializes data_sh structure
 * @data: Indicates the structure address
 * @a_vec: Indicates the argument vector
 */
void set_data(data_sh *data, char **a_vec)
{
	int x = 0;

	data->fle_name = a_vec[0];
	if (data->argvec)
	{
		data->argvec = string_tokenize1(data->argument, "\t");
		if (!data->argvec)
		{
			data->argvec = malloc(sizeof(char *) * 2);
			if (data->argvec)
			{
				data->argvec[0] = duplicate_the_string(data->argument);
				data->argvec[1] = NULL;
			}
		}
		for (x = 0; data->argvec && data->argvec[x]; x++)
			;
		data->argcount = x;

		restore_otherwise(data);
		restore_variables(data);
	}
}

/**
 * free_data - function frees data fields
 * @data: location of the structure
 * @evrthng: is if all fields are freed
 */
void free_data(data_sh *data, int evrthng)
{
	free_the_memory(data->argvec);
	data->argvec = NULL;
	data->trail = NULL;

	if (evrthng)
	{
		if (!data->command_buffer)
			free(data->argument);
		if (data->envir)
			frees_the_list(&(data->envir));
		if (data->histo_node)
			frees_the_list(&(data->histo_node));
		if (data->otherwise)
			frees_the_list(&(data->otherwise));
		free_the_memory(data->envirnmnt);
			data->envirnmnt = NULL;
		makefree((void **)data->command_buffer);
		if (data->assess_fle_descrip > 2)
			close(data->assess_fle_descrip);
		put_character(FLUSH_THE_BUFFER);
	}
}
