#include "shell.h"

/**
 * tknize - function tokenizes string.
 * @strng: indicates string
 * Return: array of string.
*/
char **tknize(char *strng)
{
	char *tkn, **tkns = NULL, s[] = " \n\t";
	int x = 0;

	if (!strng)
		return (NULL);

	tkn = strtok(strng, s);
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
		tkn = strtok(NULL, s);
		x++;
	}
	tkns[x] = NULL;
	return (tkns);
}
/**
 * g_evr - indicates function env path
 * @env_lbl: indicates the path name
 * Return: string is returned or null if otherwise
*/
char *g_evr(char *env_lbl)
{
	int x = 0, c, lnk;

	lnk = slen(env_lbl);
	while (environ[x] != NULL)
	{
		for (c = 0; environ[x][c] && c < lnk; c++)
			if (environ[x][c] == '=' || environ[x][c] != env_lbl[c])
				break;

		if (c == lnk && environ[x][c] == '=')
			return (environ[x] + lnk + 1);

		x++;
	}
	return (NULL);
}
/**
 * g_comnd - function looks if command exists in path
 * @comnd: the command
 * Return: full path of command
*/

char *g_comnd(char *comnd)
{
	char *p, *t, *cmd;
	struct stat st;

	if (stat(comnd, &st) == 0)
		return (comnd);

	p = g_evr("PATH");
	t = strtok(p, ":");
	while (t)
	{
		cmd = malloc((slen(t) + slen(comnd) + 2) * sizeof(char));
		scopy(cmd, t);
		scncat(cmd, "/");
		scncat(cmd, comnd);
		if (stat(cmd, &st) == 0)
			return (cmd);
		free(cmd);
		t = strtok(NULL, ":");
	}
	return (NULL);
}


/**
 * tkn_free - functions free tokens
 * @tkn: the array string.
*/
void tkn_free(char **tkn)
{

	if (!tkn)
		return;

	free(tkn[0]);

	free(tkn);
}

/**
 * ext_sh - function exits program
 * @tkn: string array
 * @arv: the argument vector
 * @dsh: num line
 * @stats: the status
 * @bufr: the buffer
*/
void ext_sh(char **tkn, char **arv, int dsh, int stats, char *bufr)
{
	int cde;

	if (scmp(tkn[0], "exit") == 0)
	{
		if (tkn[1])
		{
			cde = mk_asctoint(tkn[1]);
			if (cde < 0)
			{
				invalid_num(arv[0], dsh, tkn[1]);
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
		exit(stats);
	}
}
