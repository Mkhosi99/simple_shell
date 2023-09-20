#include "shell.h"


/**
 * mk_strnglenth - function will return length of a string
 * @a: indicates the string to be used
 *
 * Return: length of string will be returned
 */
int mk_strnglenth(const char *a)
{
	int x = 0;

	if (!a)
		return (-1);
	while (a[x])
		x++;
	return (x);
}

/**
 * *mk_strngcopy -  function will copy a string
 * @end: indicates the end of string
 * @start: indictates the start of string
 *
 * Return: end pointer value will be returned
 */

char *mk_strngcopy(char *end, char *start)
{
	int x = 0;

	while (start[x] != '\0')
	{
		end[x] = start[x];
		x++;
	}

	return (end);
}

/**
 * *mk_strngcncat - function will concatenate two strings
 * @end: indicates the end of string
 * @start: indicates the start of string
 *
 * Return: end pointer will be returned as result
 */
char *mk_strngcncat(char *end, char *start)
{
	int x, y;

	x = 0;

	while (end[x])
	{
		x++;
	}

	for (y = 0; start[y] != '\0'; y++)
	{
		end[x] = start[y];
		x++;
	}
	return (end);
}

/**
 * mk_strngcmpre - function will compare two strings
 * @str1: indicates the first string.
 * @str2: indicates the second string.
 *
 * Return: int result will be returned
 */
int mk_strngcmpre(char *str1, char *str2)
{
	while (*str1 != '\0' && *str2 != '\0')
	{
		if (*str1 != *str2)
		{
			return (*str1 - *str2);
		}
		str1++;
		str2++;
	}
	return (0);
}
