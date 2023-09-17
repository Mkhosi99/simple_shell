#include "shell.h"

/**
 * string_tokenize1 - function will split string into words
 * @strng: string serving as input
 * @dlm: string serving as delimeter
 * Return: will pointer to the array with strings or NULL if not
 */
char **string_tokenize1(char *strng, char *dlm)
{
	int x, y, z, g, wrdNmb = 0;
	char **st;

	if (strng == NULL || strng[0] == 0)
		return (NULL);
	if (!dlm)
		dlm = " ";
	for (x = 0; strng[x] != '\0'; x++)
		if (!the_dlm(strng[x], dlm) && (the_dlm(strng[x + 1], dlm) || !strng[x + 1]))
			wrdNmb++;

	if (wrdNmb == 0)
		return (NULL);
	st = malloc((1 + wrdNmb) * sizeof(char *));
	if (!st)
		return (NULL);
	for (x = 0, y = 0; y < wrdNmb; y++)
	{
		while (the_dlm(strng[x], dlm))
			x++;

		z = 0;
		while (!the_dlm(strng[x + z], dlm) && strng[x + z])
			z++;
		st[y] = malloc((z + 1) * sizeof(char));
		if (!st[y])
		{
			for (z = 0; z < y; z++)
				free(st[z]);
			free(st);
			return (NULL);
		}

		for (g = 0; g < z; g++)
			st[y][g] = strng[x++];
		st[y][g] = 0;
	}
	st[y] = NULL;
	return (st);
}

/**
 * string_tokenize2 - function splits string into words
 * @strng: indicates input string
 * @dlm: indicates the delimeter
 * Return: pointer to the array of strings or is NULL if not working
 */
char **string_tokenize2(char *strng, char dlm)
{
	int x, y, z, g, wrdNum = 0;
	char **st;

	if (strng == NULL || strng[0] == 0)
		return (NULL);
	for (x = 0; strng[x] != '\0'; x++)
		if ((strng[x] != dlm && strng[x + 1] == dlm) ||
				(strng[x] != dlm && !strng[x + 1]) || strng[x + 1] == dlm)
			wrdNum++;
	if (wrdNum == 0)
		return (NULL);
	st = malloc((1 + wrdNum) * sizeof(char *));
	if (!st)
		return (NULL);
	for (x = 0, y = 0; y < wrdNum; y++)
	{
		while (strng[x] == dlm && strng[x] != dlm)
			x++;
		z = 0;
		while (strng[x + z] != dlm && strng[x + z] && strng[x + z] != dlm)
			z++;
		st[y] = malloc((z + 1) * sizeof(char));
		if (!st[y])
		{
			for (z = 0; z < y; z++)
				free(st[x]);
			free(st);
			return (NULL);
		}
		for (g = 0; g < z; g++)
			st[y][g] = strng[x++];
		st[y][g] = 0;
	}
	st[y] = NULL;
	return (st);
}
