#include "shell.h"

/**
 * copy_the_string - Function copies a string
 * @end: The of the string to copy
 * @start: The start of the string
 * @x: Indicates the number of chars tha should be copied
 * Return: Concatenated string should be returned
 */
char *copy_string(char *end, char *start, int x)
{
	int a, b;
	char *strng = end;

	a = 0;
	while (start[a] != '\0' && a < x - 1)
	{
		end[a] = start[a];
		a++;
	}
	if (a < x)
	{
		b = a;
		while (b < x)
		{
			end[b] = '\0';
			b++;
		}
	}
	return (strng);
}

/**
 * concatenate_strings - Function concats strings
 * @start: Idicates the first string
 * @end: Indicates the second string
 * @x: Indicates the max bytes
 * Return: return the concatenated string
 */
char *concatenate_strings(char *start, char *end, int x)
{
	int a, b;
	char *strng = start;

	a = 0;
	b = 0;
	while (start[a] != '\0')
		a++;
	while (end[b] != '\0' && b < x)
	{
		start[a] = end[b];
		a++;
		b++;
	}
	if (b < x)
		start[a] = '\0';
	return (strng);
}

/**
 * the_string_character - Function looks for a character in string
 * @strng: Indicates the string to be analyzed
 * @m: The character that must be looked for
 * Return: return (strng)
 */
char *the_string_character(char *strng, char m)
{
	do {
		if (*strng == m)
			return (strng);
	} while (*strng++ != '\0');

	return (NULL);
}
