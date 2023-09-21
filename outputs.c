#include "shell.h"

/**
 * outpt_env - function will print enviroment using global variable
 * @ep: the environment
*/
void outpt_env(char **ep)
{
	int x = 0;

	while (ep[x])
	{
		ps(ep[x]);
		pchar('\n');
		x++;
	}
}

/**
 * cant_find - function will print error message
 * @arv: the program
 * @dsh: num line
 * @comnd: the command
 *
*/
void cant_find(char *arv, int dsh, char *comnd)
{
	sps(arv);
	sps(": ");
	mk_cnvrt(dsh);
	sps(": ");
	sps(comnd);
	sps(": not found\n");
}

/**
 * invalid_num - function will print error message
 * @arv: the program
 * @dsh: num line
 * @numb: number to exit
 *
*/
void invalid_num(char *arv, int dsh, char *numb)
{
	sps(arv);
	sps(": ");
	mk_cnvrt(dsh);
	sps(": exit: Illegal number: ");
	sps(numb);
	sps("\n");
}

/**
 * error_perm - function will print error message
 * @arv: the program
 * @dsh: num line.
 * @comnd: the command
 *
*/

void error_perm(char *arv, int dsh, char *comnd)
{
	sps(arv);
	sps(": ");
	mk_cnvrt(dsh);
	sps(": ");
	sps(comnd);
	sps(": Permission denied\n");
}
