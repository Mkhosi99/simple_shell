#include "shell.h"

/**
 * ascii_to_int_err - Function changes a string to an int
 * @strng: String that will switch to interger
 *
 * Return: return zero is no numbers are present in string,
 *         and -1 if otherwise
 */
int ascii_to_int_err(char *strng)
{
	int x = 0;
	unsigned long int answer = 0;

	if (*strng == '+')
		strng++;
	for (x = 0; strng[x] != '\0'; x++)
	{
		if (strng[x] >= '0' && strng[x] <= '9')
		{
			answer *= 10;
			answer += (strng[x] - '0');
			if (answer > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (answer);
}

/**
 * output_error - Function outputs an error message
 * @data: Indicates the parameter in the function
 * @strng_e: Indicates string holding error type
 * Return: return 0 if no numbers are present in string,
 *         return -1 if error happens
 */
void output_error(data_sh *data, char *strng_e)
{
	_puts_e(data->fle_name);
	_puts_e(": ");
	output_d_sh(data->line_add, STDERR_FILENO);
	_puts_e(": ");
	_puts_e(data->argvec[0]);
	_puts_e(": ");
	_puts_e(": ");
	_puts_e(strng_e);
}

/**
 * output_d_sh - Function outputs a number of base 10
 * @insert: Indicates the input
 * @fle_descrip: Indicates the file descriptor
 * Return: The number of characters printed will be returned
 */
int output_d_sh(int insert, int fle_descrip)
{
	int (*outpt_char)(char) = put_character;
	int x, add = 0;
	unsigned int a_a, present;

	if (fle_descrip == STDERR_FILENO)
		outpt_char = _putschar_e;
	if (insert < 0)
	{
		a_a = -insert;
		outpt_char('_');
		add++;
	}
	else
		a_a = insert;
	present = a_a;
	for (x = 1000000000; x > 1; x /= 10)
	{
		if (a_a / x)
		{
			outpt_char('0' + present / x);
			add++;
		}
		present %= x;
	}
	outpt_char('0' + present);
	add++;

	return (add);
}

/**
 * transform_number - Function converts int to string
 * @numbr: Parameter indicating the number
 * @root: Parameter indicating the base
 * @symbl: Parameter indicating argument flag
 * Return: The string should be returned
 */
char *transform_number(long int numbr, int root, int symbl)
{
	static char *order;
	static char screen[50]; /* buffer */
	char hint = 0;
	char *point;
	unsigned long x = numbr;

	if (!(symbl & TRANSFORM_LOWERCASE) && numbr < 0)
	{
		x = -numbr;
		hint = '-';
	}
	order = symbl & TRANSFORM_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	point = &screen[49];
	*point = '\0';

	do	{
		*--point = order[x % root];
		x /= root;
	} while (x != 0);

	if (hint)
		*--point = hint;
	return (point);
}

/**
 * eliminate_comments - Function replaces '#' with '\0'
 * @screen:The address of the string that must be modified
 *
 * Return: return should always be zero
 */
void eliminate_comments(char *screen)
{
	int x;

	for (x = 0; screen[x] != '\0'; x++)
		if (screen[x] == '#' && (!x || screen[x - 1] == ' '))
		{
			screen[x] = '\0';
			break;
		}
}
