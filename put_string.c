#include "shell.h"


/**
 * mk_writechar - function will write the char to stdout
 * @a: will be the char to print
 */
void mk_writechar(char a)
{
	write(1, &a, 1);
}

/**
 * mk_writes - function will print a string
 *
 * @str: indicates the characters used
 */
void mk_writes(char *str)
{
	int x = 0;

	if (!str)
		return;

	while (str[x])
	{
		mk_writechar(str[x]);
		x++;
	}
}

/**
 * mk_cwritechar - function will write char to stderr
 * @a: indicates the character to be printed
 */
void mk_cwritechar(char a)
{
	if (a)
		write(2, &a, 1);
}

/**
 * mk_swrites - function will print string to stderr
 *
 * @str: indicates the characters used
 */
void mk_swrites(char *str)
{
	int x = 0;

	if (!str)
		return;

	while (str[x] != '\0')
	{
		mk_cwritechar(str[x]);
		x++;
	}
}
