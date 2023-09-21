#include "shell.h"


/**
 * c_evr - function looks if a command is env
 * @tkn: string array
 * @env: the enviroment
 * @bufr: the buffer
 * Return: will be -1 on success or 0 otherwise
*/
int c_evr(char **tkn, char **env, char *bufr)
{
	if (scmp(tkn[0], "env") == 0)
	{
		outpt_env(env);
		free(tkn);
		free(bufr);
		return (-1);
	}
	return (0);
}
/**
 * g_tkn - function reads line
 * @bufr: the buffer
 * @stats: the status
 * Return: string array
*/
char **g_tkn(char **bufr, int stats)
{

	size_t sB = 0;
	int lc;

	lc = getline(bufr, &sB, stdin);
	if (lc == -1)
	{
		free(*bufr);
		exit(stats);
	}

	return (tknize(*bufr));
}

/**
 * exe_comnd - function executes command
 * @tkn: array of string
 * @arv: argument vector.
 * @dsh: line number
 * @env: enviroment
 * Return: error of number
*/
int exe_comnd(char **tkn, char **arv, int dsh, char **env)
{
	char *cm;

	cm = g_comnd(tkn[0]);
	if (execve(cm, tkn, env) == -1)
	{
		if (!cm)
		{
			cant_find(arv[0], dsh, tkn[0]);
			free(cm);
			free(tkn);
			return (121);
		}
		if (errno == EACCES)
		{
			error_perm(arv[0], dsh, tkn[0]);
			free(cm);
			free(tkn);
			return (120);
		}

		free(cm);
		free(tkn);
		perror("Error");
		return (errno);
	}
	free(cm);
	free(tkn);
	return (0);
}

/**
 * main - main function
 * @arc: the count argcount
 * @arv: the arg vector
 * @env: the enviroment
 * Return: will return 0 on success
*/
int main(int __attribute__((unused)) arc, char **arv, char **env)
{
	char **tk, *bfr;
	int sts, idn, rs = 1, scde = 0;

	bfr = NULL;
	tk = NULL;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(1, "$ ", 2);

		tk = g_tkn(&bfr, scde);

		if (!tk || !tk[0])
		{
			rs++;
			free(tk);
			continue;
		}
		ext_sh(tk, arv, rs, scde, bfr);
		if (c_evr(tk, env, bfr) == -1)
			continue;

		idn = fork();
		if (idn == 0)
		{
			return (exe_comnd(tk, arv, rs, env));
		}
		else
		{
			wait(&sts);
			if (WIFEXITED(sts))
			{
				scde = WEXITSTATUS(sts);
			}
		}
		free(tk);
		free(bfr);
		rs++;
	}
	return (0);
}
