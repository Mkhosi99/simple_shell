#include "shell.h"

/**
 * insert_buffr - Function buffer chained commands
 * @data: Indicates the parameter
 * @bufr: Indicates location of the buffer(bufr)
 * @rnge: Indicates location of the rnge variable
 * Return: return the bytes
 */
ssize_t insert_buffr(data_sh *data, char **bufr, size_t *rnge)
{
	ssize_t x = 0;
	ssize_t rnge_x = 0;

	if (!*rnge) /* is buffer is empty, it should be filled */
	{
		free(*bufr);
		*bufr = NULL;
		signal(SIGINT, int_handle);
#if READ_GETLINE
		x = getline(bufr, &rnge_x, stdin);
#else
		x = fetch_line(data, bufr, &rnge_x);
#endif
		if (x > 0)
		{
			if ((*bufr)[x - 1] == '\n')
			{
				(*bufr)[x - 1] = '\0';
				x--;
			}
			data->line_add_symbol = 1;
			eliminate_comments(*bufr);
			construct_hist_list(data, *bufr, data->add_up_histo++);
			{
				*rnge = x;
				data->command_buffer = bufr;
			}
		}
	}
	return (x);
}

/**
 * fetch_input - Function includes line without the newline
 * @data: Indicates the parameter
 * Return: returns the bytes read in function
 */
ssize_t fetch_input(data_sh *data)
{
	static char *bufr;
	static size_t a, b, rnge;
	ssize_t x = 0;
	char **bufr_x = data->argvec, *point;

	put_character(FLUSH_THE_BUFFER);
	x = insert_buffr(data, &bufr, &rnge);
	if (x == -1)
		return (-1);
	if (rnge)
	{
		b = a;
		point = bufr + a;

		look_at_chain(data, bufr, &b, a, rnge);
		while (b < rnge)
		{
			if (the_chain(data, bufr, &b))
				break;
			b++;
		}

		a = b + 1;
		if (a >= rnge)
		{
			a = rnge = 0;
			data->buffer_type_command = COMMAND_NORMAL;
		}

		*bufr_x = point;
		return (the_string_lenth(point));
	}

	*bufr_x = bufr;
	return (x);
}

/**
 * scan_bufr - Function reads buffer
 * @data: Indictaes the parameter in function
 * @bufr: Indicates the buffer
 * @x: Indicates the size
 *
 * Return: function should return variable a
 */
ssize_t scan_bufr(data_sh *data, char *bufr, size_t *x)
{
	ssize_t a = 0;

	if (*x)
		return (0);
	a = read(data->assess_fle_descrip, bufr, READ_THE_BUFFER_SIZE);
	if (a >= 0)
		*x = a;
	return (a);
}

/**
 * fetch_line - Function includes next line from STDIN
 * @data: The parameter in function
 * @point: points to address of buffer
 * @lenth: Indicates the size of preallocated point buffer
 *         or NULL
 *
 * Return: function should return m
 */
int fetch_line(data_sh *data, char **point, size_t *lenth)
{
	static char bufr[READ_THE_BUFFER_SIZE];
	static size_t x, rnge;
	size_t z;
	ssize_t w = 0, m = 0;
	char *pter = NULL, *new_pter = NULL, *d;

	pter = *point;
	if (pter && lenth)
		m = *lenth;
	if (x == rnge)
		x = rnge = 0;

	w = scan_bufr(data, bufr, &rnge);
	if (w == -1 || (w == 0 && rnge == 0))
		return (-1);

	d = the_string_character(bufr + x, '\n');
	z = d ? 1 + (unsigned int)(d - bufr) : rnge;
	new_pter = resize_mem(pter, m, m ? m + z : z + 1);
	if (!new_pter)
		return (pter ? free(pter), -1 : -1);

	if (m)
		concatenate_strings(new_pter, bufr + x, z - x);
	else
		copy_string(new_pter, bufr + x, z - x + 1);

	m += z - x;
	x = z;
	pter = new_pter;

	if (lenth)
		*lenth = m;
	*point = pter;
	return (m);
}

/**
 * int_handle - Functions will block use of ctrl-C
 * @numbr_sig: Indicates signal number
 *
 * Return: Function returns void
 */
void int_handle(__attribute__((unused))int numbr_sig)
{
	put_string("\n");
	put_string("$ ");
	put_character(FLUSH_THE_BUFFER);
}
