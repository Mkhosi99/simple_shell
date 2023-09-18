#include "shell.h"

/**
 * copy_the_string - function will copy a string
 * @endng: the end
 * @strtng: the start
 * Return: will be pointers to destination
 */

char *copy_the_string(char *endng, char *strtng)
{
	int x = 0;

	if (endng == strtng || strtng == 0)
		return (endng);
	while (strtng[x])
	{
		endng[x] = strtng[x];
		x++;
	}
	endng[x] = 0;
	return (endng);
}

/**
 * duplicate_the_string - function duplicates string
 *@strng: string to be duplicated
 *Return: pointer of duplicated string
 */

char *duplicate_the_string(const char *strng)
{
	int lenth = 0;
	char *dupl;

	if (strng == NULL)
		return (NULL);
	while (*strng++)
		lenth++;
	dupl = malloc(sizeof(char) * (lenth + 1));

	if (!dupl)
		return (NULL);
	for (lenth++; lenth--;)
		dupl[lenth] = *--strng;
	return (dupl);
}

/**
 * put_string - function outputs an input string
 * @strng: the string that must be print
 * Return: will be void
 */
void put_string(char *strng)
{
	int x = 0;

	if (!strng)
		return;
	while (strng[x] != '\0')
	{
		put_character(strng[x]);
		x++;
	}
}

/**
 * put_character - function writes character a to stdout
 * @a: indicates the character to be printed
 * Return: will be 1 if successful and -1 if if not
 */

int put_character(char a)
{
	static int x;
	static char bufr[WRITE_THE_BUFFER_SIZE];

	if (a == FLUSH_THE_BUFFER || x >= WRITE_THE_BUFFER_SIZE)
	{
		write(1, bufr, x);
		x = 0;
	}
	if (a != FLUSH_THE_BUFFER)
		bufr[x++] = a;
	return (1);
}
