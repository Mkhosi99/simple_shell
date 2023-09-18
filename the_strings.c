#include "shell.h"

/**
 * the_string_lenth - functions returns length of string
 * @strng: the string to assess
 * Return: number of string length will be returned
 */
int the_string_lenth(char *strng)
{
	int x = 0;

	if (!strng)
		return (0);

	while (*strng++)
		x++;
	return (x);
}

/**
 * the_string_compare - function compares two strings
 * @strng1: indicates the first string
 * @strng2: indicates the second string
 * Return: -1 if strng1 < strng2 and 1 if strng1 > strng2
 *         will be 0 if they are equal to each other
 */
int the_string_compare(char *strng1, char *strng2)
{
	while (*strng1 && *strng2)
	{
		if (*strng1 != *strng2)
			return (*strng1 - *strng2);
		strng1++;
		strng2++;
	}
	if (*strng1 == *strng2)
		return (0);
	else
		return (*strng1 < *strng2 ? -1 : 1);
}

/**
 * begins_with - function assesses what a string starts with
 * @big: indicates the string to be searched
 * @small: indicates the substring to be determined
 * Return: will be address of the next character in big or NULL
 */
char *begins_with(const char *big, const char *small)
{
	while (*small)
		if (*small++ != *big++)
			return (NULL);
	return ((char *)big);
}

/**
 * concatenate_the_strings - function will concat two strings
 * @endng: the last buffer
 * @strtng: the starting buffer
 * Return: points to the last buffer
 */
char *concatenate_the_strings(char *endng, char *strtng)
{
	char *cncat = endng;

	while (*endng)
		endng++;
	while (*strtng)
		*endng++ = *strtng++;
	*endng = *strtng;
	return (cncat);
}
