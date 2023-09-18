#include "shell.h"

/**
 * the_command - the function determines if file is
 * executable
 * @data: the param
 * @trail: indicates path to file
 * Return: will be 1 else 0 if not
 */
int the_command(data_sh *data, char *trail)
{
	struct stat ts;

	(void)data;
	if (!trail || stat(trail, &ts))
		return (0);

	if (ts.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * matching_character - function duplicates characters
 * @trailstr: indicates the path string
 * @begn: indicates the starting index
 * @cancel: indicates the stopping index
 * Return: points to the new buffer
 */
char *matching_character(char *trailstr, int begn, int cancel)
{
	static char bufr[1024];
	int x = 0, y = 0;

	for (y = 0, x = begn; x < cancel; x++)
		if (trailstr[x] != ':')
			bufr[y++] = trailstr[x];
	bufr[y] = 0;
	return (bufr);
}

/**
 * look_for_path - function finds command in path string
 * @data: the info param
 * @trailstr: indicates path of string
 * @comnd: indicates the command to find
 * Return: the whole path of comnd or NULL if not found
 */
char *look_for_path(data_sh *data, char *trailstr, char *comnd)
{
	int x = 0, pre_post = 0; /* present position */
	char *trail;

	if (!trailstr)
		return (NULL);
	if ((the_string_lenth(comnd) > 2) && begins_with(comnd, "./"))
	{
		if (the_command(data, comnd))
			return (comnd);
	}
	while (1)
	{
		if (!trailstr[x] || trailstr[x] == ':')
		{
			trail = matching_character(trailstr, pre_post, x);
			if (!*trail)
				concatenate_the_strings(trail, comnd);
			else
			{
				concatenate_the_strings(trail, "/");
				concatenate_the_strings(trail, comnd);
			}
			if (the_command(data, trail))
				return (trail);
			if (!trailstr[x])
				break;
			pre_post = x;
		}
		x++;
	}
	return (NULL);
}
