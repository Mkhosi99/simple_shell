#include "shell.h"

/**
 * output_envir - function will print enviroment using the global variable
 * @envopt: indicates the env
*/
void output_envir(char **envopt)
{
	int x = 0;

	while (envopt[x])
	{
		mk_writes(envopt[x]);
		mk_writechar('\n');
		x++;
	}
}

/**
 * not_detected - function will print error message not found.
 * @argve: indicates the program's names
 * @dash: indicates the number of lines
 * @comnd: indictaes that the command doesn't exit
 *
*/
void not_detected(char *argve, int dash, char *comnd)
{
	mk_swrites(argve);
	mk_swrites(": ");
	mk_itoa(dash);
	mk_swrites(": ");
	mk_swrites(comnd);
	mk_swrites(": not found\n");
}

/**
 * invalid_numb - function will print error message invalid numb
 * @argve: indictaes the program's name
 * @dash: indictaes the number of lines
 * @numbr: indicates the exit number
 *
*/
void invalid_numb(char *argve, int dash, char *numbr)
{
	mk_swrites(argve);
	mk_swrites(": ");
	mk_itoa(dash);
	mk_swrites(": exit: Invalid number: ");
	mk_swrites(numbr);
	mk_swrites("\n");
}

/**
 * error_perm - function will print error message Permission denied
 * @argve: program's name.
 * @dash: indicates the number of lines
 * @comnd: indicates that the command doesn't exist
 *
*/

void error_perm(char *argve, int dash, char *comnd)
{
	mk_swrites(argve);
	mk_swrites(": ");
	mk_itoa(dash);
	mk_swrites(": ");
	mk_swrites(comnd);
	mk_swrites(": Permission denied\n");
}
