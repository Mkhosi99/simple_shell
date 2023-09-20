#include "shell.h"

/**
 * split_str - function will split a string
 * @strng: the indicated string
 * Return: array of string of the string will be returned
*/
char **split_str(char *strng)
{
	char *tkn, **tkns = NULL, a[] = " \n\t";
	int x = 0;

	if (!strng)
		return (NULL);

	tkn = strtok(strng, a);
	if (!tkn)
	{
		free(strng);
		return (NULL);
	}

	tkns = malloc(sizeof(char *) * 1024);
	if (tkns == NULL)
	{
		free(tkns);
		free(strng);
		perror("realloc");
		exit(EXIT_FAILURE);
	}

	while (tkn)
	{
		tkns[x] = tkn;
		tkn = strtok(NULL, strng);
		x++;
	}
	tkns[x] = NULL;
	return (tkns);
}
/**
 * fetch_envir - function gets the enviroment path
 * @env_label: indicates the path name.
 * Return: returns the string or null if otherwise
*/
char *fetch_envir(char *env_label)
{
	int x = 0, y, labl;

	labl = mk_strnglenth(env_label);
	while (environ[x] != NULL)
	{
		for (y = 0; environ[x][y] && y < labl; y++)
			if (environ[x][y] == '=' || environ[x][y] != env_label[y])
				break;

		if (y == labl && environ[x][y] == '=')
			return (environ[x] + labl + 1);

		x++;
	}
	return (NULL);
}
/**
 * fetch_comnd - function will search if command exists in the path variable
 * @comnd: indicates the command used
 * Return: absolute path of command returned or NULL
*/

char *fetch_comnd(char *comnd)
{
	char *trail, *tkn, *comnd_trail;
	struct stat st;

	if (stat(comnd, &st) == 0)
		return (comnd);

	trail = fetch_envir("PATH");
	tkn = strtok(trail, ":");
	while (tkn)
	{
		comnd_trail = malloc((mk_strnglenth(tkn) + mk_strnglenth(comnd) + 2) * sizeof(char));
		mk_strngcopy(comnd_trail, tkn);
		mk_strngcncat(comnd_trail, "/");
		mk_strngcncat(comnd_trail, comnd);
		if (stat(comnd_trail, &st) == 0)
			return (comnd_trail);
		free(comnd_trail);
		tkn = strtok(NULL, ":");
	}
	return (NULL);
}


/**
 * release_tkn - function will free the tokens
 * @tkn: indicates the array of the string
*/
void release_tkn(char **tkn)
{

	if (!tkn)
		return;

	free(tkn[0]);

	free(tkn);
}

/**
 * ext_sh - function will exit from program
 * @tkn: indicates the array of the string
 * @argve: indicates the argument vector
 * @dash: indicates the number of lines used
 * @condition: indicates the status identity
 * @bufr: indicates the buffer used
*/
void ext_sh(char **tkn, char **argve, int dash, int condition, char *bufr)
{
	int cde;

	if (mk_strngcmpre(tkn[0], "exit") == 0)
	{
		if (tkn[1])
		{
			cde = mk_atoi(tkn[1]);
			if (cde < 0)
			{
				invalid_numb(argve[0], dash, tkn[1]);
				free(tkn);
				free(bufr);
				exit(2);
			}
			else if (cde > 255)
			{
				free(tkn);
				free(bufr);
				exit(232);
			}
			else
			{
				free(tkn);
				free(bufr);
				exit(cde);
			}
		}
		free(bufr);
		free(tkn);
		exit(condition);
	}
}
