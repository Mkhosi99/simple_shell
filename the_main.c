#include "shell.h"

/**
 * main - function entry
 * @argcnt: indicates the argument count
 * @argve: indicates the argument vector
 * Return: will return zero if working and 1 if not
 */
int main(int argcnt, char **argve)
{
	data_sh data[] = { DATA_START };
	int f_dscrp = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (f_dscrp)
			: "r" (f_dscrp));

	if (argcnt == 2)
	{
		f_dscrp = open(argve[1], O_RDONLY);
		if (f_dscrp == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_puts_e(argve[0]);
				_puts_e(": 0: Cannot open ");
				_puts_e(argve[1]);
				_putschar_e('\n');
				_putschar_e(FLUSH_THE_BUFFER);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		data->assess_fle_descrip = f_dscrp;
	}
	occupy_envir_list(data);
	look_thru_hist(data);
	shell_hsh(data, argve);
	return (EXIT_SUCCESS);
}
