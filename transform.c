#include "shell.h"

/**
 * mk_atoi - function will convert an ascii to integer.
 * @str: indicates the string.
 * Return: will return the integer
*/
int mk_atoi(const char *str)
{
	int mark = 1, root = 0, x = 0;

	while (str[x])
	{
		if (str[x] < '0' || str[x] > '9')
		{
			return (-1);
		}

		if ((root > INT_MAX / 10) || ((root == INT_MAX / 10) && (str[x] - '0' > 7)))
		{
			if (mark == 1)
				return (INT_MAX);
			else
				return (INT_MIN);
		}
		root = 10 * root + (str[x++] - '0');
	}
	return (root * mark);
}

/**
 * mk_itoa - function will convert an integer to string
 * @x: indicates the integer
*/

void mk_itoa(int x)
{
	char *str, a;
	int m = 0, remit;

	str = malloc(sizeof(char) * 11);
	if (str == NULL)
		return;


	while (x != 0)
	{
		remit = x % 10;

		x = x / 10;
		a = '0' + remit;
		str[m] = a;
		m++;
	}

	for (m -= 1; m >= 0; m--)
		_eputchar(str[m]);
	free(str);
}
