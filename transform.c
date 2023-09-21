#include "shell.h"

/**
 * mk_asctoint - function converts ascii to int
 * @s: the string
 * Return: the int
*/
int mk_asctoint(const char *s)
{
	int mark = 1, root = 0, i = 0;

	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
		{
			return (-1);
		}

		if ((root > INT_MAX / 10) || ((root == INT_MAX / 10) && (s[i] - '0' > 7)))
		{
			if (mark == 1)
				return (INT_MAX);
			else
				return (INT_MIN);
		}
		root = 10 * root + (s[i++] - '0');
	}
	return (root * mark);
}

/**
 * mk_cnvrt - function converts integer to string
 * @t: the integer
*/

void mk_cnvrt(int t)
{
	char *m, c;
	int x = 0, remit;

	m = malloc(sizeof(char) * 11);
	if (m == NULL)
		return;


	while (t != 0)
	{
		remit = t % 10;

		t = t / 10;
		c = '0' + remit;
		m[x] = c;
		x++;
	}

	for (x -= 1; x >= 0; x--)
		cpchar(m[x]);
	free(m);
}
