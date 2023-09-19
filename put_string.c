#include "shell.h"


/**
 * _putchar - function will write the char to stdout
 * @a: will be the char to print
 */
void _putchar(char a)
{
	write(1, &a, 1);
}

/**
 * _puts - function will print a string
 *
 * @str: indicates the characters used
 */
void _puts(char *str)
{
	int x = 0;

	if (!str)
		return;

	while (str[x])
	{
		_putchar(str[x]);
		x++;
	}
}

/**
 * _eputchar - function will write char to stderr
 * @a: indicates the character to be printed
 */
void _eputchar(char a)
{
	if (a)
		write(2, &a, 1);
}

/**
 * _eputs - function will print string to stderr
 *
 * @str: indicates the characters used
 */
void _eputs(char *str)
{
	int x = 0;

	if (!str)
		return;

	while (str[x] != '\0')
	{
		_eputchar(str[x]);
		x++;
	}
}
