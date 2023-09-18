#include "shell.h"

/**
 * associate - Will return if the shell is interactive
 * @data: The address of the struct
 *
 * Return: returns 1 if it interactive, or zero otherwise
 */

int associate(data_sh *data)
{
	int answer = 0;

	if (isatty(STDIN_FILENO) && data->assess_fle_descrip <= 2)
		answer = 1;

	return (answer);
}

/**
 * the_dlm - Determines if the character is a delimiter
 * @x: The character to look at
 * @dlm: Indicates the delimiter string
 *
 * Return: returns 1 if it is true or 0 if it is false
 */

int the_dlm(char x, char *dlm)
{
	int a;
	int range = strlen(dlm);

	for (a = 0; a < range; a++)
	{
		if (x == dlm[a])
			return (1);
	}

	return (0);
}

/**
 * the_alphabet - Looks for alphabetic character
 * @x: Indicates the character to input
 *
 * Return: returns 1 if x is aplhabetic or 0 if not
 */

int the_alphabet(int x)
{
	if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * ascii_to_int - Function will convert string to interger
 * @strng: The string that will be converted
 *
 * Return: returns 0 if no number are in string,
 *         or otherwise for converted number
 */

int ascii_to_int(char *strng)
{
	int x, mark = 1, symbol = 0, product = 0;
	unsigned int answer = 0;
	int range = strlen(strng);

	for (x = 0; x < range && symbol != 2; x++)
	{
		if (strng[x] == '-')
			mark *= -1;

		if (strng[x] >= '0' && strng[x] <= '9')
		{
			symbol = 1;
			answer *= 10;
			answer += (strng[x] - '0');
		}
		else if (symbol == 1)
			symbol = 2;
	}

	if (mark == -1)
		product = -answer;
	else
		product = answer;

	return (product);
}
