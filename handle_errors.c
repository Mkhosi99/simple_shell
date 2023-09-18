#include "shell.h"

/**
 * _puts_e - Function will return string input
 * @strng: The output string
 * Return: Nothing will be returned
 */

void _puts_e(char *strng)
{
	int x = 0;

	if (!strng)
		return;
	while (strng[x] != '\0')
	{
		_putschar_e(strng[x]);
		x++;
	}
}

/**
 * _putschar_e - Function writes character a to stderr
 * @a: The output character
 *
 * Return: returns 1 if success and -1 if not
 */

int _putschar_e(char a)
{
	static int x;
	static char buffr[WRITE_THE_BUFFER_SIZE];

	if (a == FLUSH_THE_BUFFER || x >= WRITE_THE_BUFFER_SIZE)
	{
		write(2, buffr, x);
		x = 0;
	}
	if (a != FLUSH_THE_BUFFER)
		buffr[x++] = a;
	return (1);
}

/**
 * _put_fle_descrip - Function writes character a to fle_descrip
 * @a: The output character
 * @fle_descrip: Indicates the file descriptor to be written
 *
 * Return: returns 1 if success and -1 if not
 */

int _put_fle_descrip(char a, int fle_descrip)
{
	static int x;
	static char buffr[WRITE_THE_BUFFER_SIZE];

	if (a == FLUSH_THE_BUFFER || x >= WRITE_THE_BUFFER_SIZE)
	{
		write(fle_descrip, buffr, x);
		x = 0;
	}
	if (a != FLUSH_THE_BUFFER)
		buffr[x++] = a;
	return (1);
}

/**
 * _puts_fle_descrip - Function outputs input string
 * @string: The output string
 * @fle_descrip: Indicates the file descriptor to be written
 *
 * Return: Number of characters included
 */

int _puts_fle_descrip(char *string, int fle_descrip)
{
	int x = 0;

	if (!string)
		return (0);
	while (*string)
	{
		x += _put_fle_descrip(*string++, fle_descrip);
	}
	return (x);
}
