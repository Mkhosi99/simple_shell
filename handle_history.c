#include "shell.h"

/**
 * fetch_hist_fle - function fetches history file
 * @data: indicates the parameter
 *
 * Return: indicates the string thas has history file
 */
char *fetch_hist_fle(data_sh *data)
{
	char *bufr, *drec;

	drec = get_envir(data, "HOME=");
	if (!drec)
		return (NULL);

	bufr = malloc(sizeof(char) * (the_string_lenth(drec)
				+ the_string_lenth(FILE_HISTORY) + 2));
	if (!bufr)
		return (NULL);
	bufr[0] = 0;
	copy_the_string(bufr, drec);
	concatenate_the_strings(bufr, "/");
	concatenate_the_strings(bufr, FILE_HISTORY);
	return (bufr);
}

/**
 * note_hist - function makes or appends existing file
 * @data: indicates the parameter
 * Return: return 1 if working or -1 otherwise
 */
int note_hist(data_sh *data)
{
	ssize_t f_descrp;
	char *fle_nme = fetch_hist_fle(data);
	list_sh *nde = NULL;

	if (!fle_nme)
		return (-1);

	f_descrp = open(fle_nme, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fle_nme);
	if (f_descrp == -1)
		return (-1);
	for (nde = data->histo_node; nde; nde = nde->nextNode)
	{
		_puts_fle_descrip(nde->string, f_descrp);
		_put_fle_descrip('\n', f_descrp);
	}
	_put_fle_descrip(FLUSH_THE_BUFFER, f_descrp);
	close(f_descrp);
	return (1);
}

/**
 * look_thru_hist - function reads files history
 * @data: indicates the parameter
 * Return: will return history count if working or 0 if not
 */
int look_thru_hist(data_sh *data)
{
	int x, ends = 0, sum_line = 0;
	ssize_t f_dscrp, looklen, rnge = 0;
	struct stat ts;
	char *bufr = NULL, *fle_nme = fetch_hist_fle(data);

	if (!fle_nme)
		return (0);

	f_dscrp = open(fle_nme, O_RDONLY);
	free(fle_nme);
	if (f_dscrp == -1)
		return (0);
	if (!fstat(f_dscrp, &ts))
		rnge = ts.st_size;
	if (rnge < 2)
		return (0);
	bufr = malloc(sizeof(char) * (rnge + 1));
	if (!bufr)
		return (0);
	looklen = read(f_dscrp, bufr, rnge);
	bufr[rnge] = 0;
	if (looklen <= 0)
		return (free(bufr), 0);
	close(f_dscrp);
	for (x = 0; x < rnge; x++)
		if (bufr[x] == '\n')
		{
			bufr[x] = 0;
			construct_hist_list(data, bufr + ends, sum_line++);
			ends = x + 1;
		}
	if (ends != x)
		construct_hist_list(data, bufr + ends, sum_line++);
	free(bufr);
	data->add_up_histo = sum_line;
	while (data->add_up_histo-- >= MAXIMUM_HISTORY)
		remove_node_at_indicator(&(data->histo_node), 0);
	renumb_hist(data);
	return (data->add_up_histo);
}

/**
 * construct_hist_list - function will add entry to history linked list
 * @data: param struct with likely arguments
 * @bufr: indicates the buffer
 * @sum_line: indicates the history count
 * Return: Should always return 0
 */
int construct_hist_list(data_sh *data, char *bufr, int sum_line)
{
	list_sh *nde = NULL;

	if (data->histo_node)
		nde = data->histo_node;
	attach_node_at_end(&nde, bufr, sum_line);

	if (!data->histo_node)
		data->histo_node = nde;
	return (0);
}

/**
 * renumb_hist - function renumber history linked list after alterrations
 * @data: param with likely arguments
 * Return: should return new add_up_histo
 */
int renumb_hist(data_sh *data)
{
	list_sh *nde = data->histo_node;
	int x = 0;

	while (nde)
	{
		nde->int_num = x++;
		nde = nde->nextNode;
	}
	return (data->add_up_histo = x);
}
