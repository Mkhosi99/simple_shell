#include "shell.h"


/**
 * comnd_envir - function looks if command is a env and will execute it
 * @tkn: the array of the string
 * @envir: indicates the enviroment
 * @bufr: indicates the buffer.
 * Return: will return -1 if env is the command and 0 if not
*/
int comnd_envir(char **tkn, char **envir, char *bufr)
{
	if (_strcmp(tkn[0], "env") == 0)
	{
		output_envir(envir);
		free(tkn);
		free(bufr);
		return (-1);
	}
	return (0);
}
/**
 * fetch_tkn - function will read line add return tokens
 * @bufr: indicates the buffer
 * @condition:indicates the status
 * Return: array of string will be returned
*/
char **fetch_tkn(char **bufr, int condition)
{

	size_t x = 0;
	int lenth;

	lenth = getline(bufr, &x, stdin);
	if (lenth == -1)
	{
		free(*bufr);
		exit(condition);
	}

	return (split_str(*bufr));
}

/**
 * exec_comnd - function will execute a command
 * @tkn: indicates the array of string
 * @argve: the argument vector.
 * @dash: indicates the number of lines
 * @envir: indicates the enviroment
 * Return: will return the error number
*/
int exec_comnd(char **tkn, char **argve, int dash, char **envir)
{
	char *comnd;

	comnd = fetch_comnd(tkn[0]);
	if (execve(comnd, tkn, envir) == -1)
	{
		if (!comnd)
		{
			not_detected(argve[0], dash, tkn[0]);
			free(comnd);
			free(tkn);
			return (127);
		}
		if (errno == EACCES)
		{
			error_perm(argve[0], dash, tkn[0]);
			free(comnd);
			free(tkn);
			return (126);
		}

		free(comnd);
		free(tkn);
		perror("Error");
		return (errno);
	}
	free(comnd);
	free(tkn);
	return (0);
}

/**
 * main - main function
 * @argcnt: the arg count
 * @argve: the arg vector
 * @envir: indicates the enviroment
 * Return: will return 0 on Success
*/
int main(int __attribute__((unused)) argcnt, char **argve, char **envir)
{
	char **tkn, *bufr;
	int condition, iden, x = 1, cond_code = 0;

	bufr = NULL;
	tkn = NULL;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(1, "$ ", 2);

		tkn = fetch_tkn(&bufr, cond_code);

		if (!tkn || !tkn[0])
		{
			x++;
			free(tkn);
			continue;
		}
		ext_sh(tkn, argve, x, cond_code, bufr);
		if (comnd_envir(tkn, envir, bufr) == -1)
			continue;

		iden = fork();
		if (iden == 0)
		{
			return (exec_comnd(tkn, argve, x, envir));
		}
		else
		{
			wait(&condition);
			if (WIFEXITED(condition))
			{
				cond_code = WEXITSTATUS(condition);
			}
		}
		free(tkn);
		free(bufr);
		x++;
	}
	return (0);
}
