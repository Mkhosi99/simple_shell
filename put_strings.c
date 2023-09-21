#include "shell.h"


/**
 * pchar - function will write char to stdout
 * @c: The character to print
 */
void pchar(char c)
{
	write(1, &c, 1);
}

/**
 * ps - function will print string
 *
 * @s: the characters
 */
void ps(char *s)
{
	int x = 0;

	if (!s)
		return;

	while (s[x])
	{
		pchar(s[x]);
		x++;
	}
}

/**
 * cpchar - function will write char to stderr
 * @c: The character to print
 */
void cpchar(char c)
{
	if (c)
		write(2, &c, 1);
}

/**
 * sps -  function will print string to stderr.
 *
 * @s: the characters
 */
void sps(char *s)
{
	int x = 0;

	if (!s)
		return;

	while (s[x] != '\0')
	{
		cpchar(s[x]);
		x++;
	}
}
