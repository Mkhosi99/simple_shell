#include "shell.h"


/**
 * slen - function determines length of string
 * @s: the string used
 *
 * Return: length of string
 */
int slen(const char *s)
{
	int x = 0;

	if (!s)
		return (-1);
	while (s[x])
		x++;
	return (x);
}

/**
 * scopy - function copies string
 * @de: the destination
 * @sr: the source
 *
 * Return: value the pointer to dest
 */

char *scopy(char *de, char *sr)
{
	int x = 0;

	while (sr[x] != '\0')
	{
		de[x] = sr[x];
		x++;
	}

	return (de);
}

/**
 * scncat - function will concat strings
 * @de: the destination
 * @sr: the string
 *
 * Return: concat string
 */
char *scncat(char *de, char *sr)
{
	int x, j;

	x = 0;

	while (de[x])
	{
		x++;
	}

	for (j = 0; sr[j] != '\0'; j++)
	{
		de[x] = sr[j];
		x++;
	}
	return (de);
}

/**
 * scmp - function will compare strings
 * @st1: the first string
 * @st2: the second string
 *
 * Return: int comparison result
 */
int scmp(char *st1, char *st2)
{
	while (*st1 != '\0' && *st2 != '\0')
	{
		if (*st1 != *st2)
		{
			return (*st1 - *st2);
		}
		st1++;
		st2++;
	}
	return (0);
}
