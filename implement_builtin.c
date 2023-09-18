#include "shell.h"

/**
 * the_exit - Function exits the shell
 * @data: The structure that has the arguments
 *
 * Return: Will exit with a given exit status
 *         (0) if info.argvec[0] != "exit"
 */

int the_exit(data_sh *data)
{
	int assess_exit;

	if (data->argvec[1])
	{
		assess_exit = ascii_to_int_err(data->argvec[1]);
		if (assess_exit == -1)
		{
			data->condition = 2;
			output_error(data, "Incorrect number: ");
			_puts_e(data->argvec[1]);
			_putschar_e('\n');
			return (1);
		}
		data->int_error = ascii_to_int_err(data->argvec[1]);
		return (-2);
	}
	data->int_error = -1;
	return (-2);
}

/**
 * the_cd - Function will change cd
 * @data: The construction with the arguments,
 *        It will be used to maintain a constant function prototype
 * Return: Will always be zero
 */

int the_cd(data_sh *data)
{
	char *a, *direc, buff[1024];
	int alt_direc;

	a = getcwd(buff, 1024);
	if (!a)
		put_string("Execute: >>getcwd fail message here<<\n");
	if (!data->argvec[1])
	{
		direc = get_envir(data, "HOME=");
		if (!direc)
			alt_direc = /* Execute: What should this be? */
				chdir((direc = get_envir(data, "PWD=")) ? direc : "/");
		else
			alt_direc = chdir(direc);
	}
	else if (the_string_compare(data->argvec[1], "-") == 0)
	{
		if (!get_envir(data, "PREVIOUSPWD="))
		{
			put_string(a);
			put_character('\n');
			return (1);
		}
		put_string(get_envir(data, "PREVIOUSPWD=")), put_character('\n');
		alt_direc = /* Execute: What should this be? */
			chdir((direc = get_envir(data, "PREVIOUSPWD=")) ? direc : "/");
	}
	else
		alt_direc = chdir(data->argvec[1]);
	if (alt_direc == -1)
	{
		output_error(data, "Cannot cd into ");
		_puts_e(data->argvec[1]), _putschar_e('\n');
	}
	else
	{
		set_envir(data, "PREVIOUSPWD", get_envir(data, "PWD="));
		set_envir(data, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * the_help - Changes the present directory of the process
 * @data: The shape with potential arguments,
 *        Is used to maintain constant function prototype
 *
 * Return: returns always zero
 */

int the_help(data_sh *data)
{
	char **argmnt_arr;

	argmnt_arr = data->argvec;
	put_string("The help call operates. Function not yet executed \n");
	if (0)
		put_string(*argmnt_arr);
	return (0);
}
