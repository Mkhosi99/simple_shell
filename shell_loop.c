#include "shell.h"

/**
 * shell_hsh - the function indicates
 * the main shell loop
 * @data: the param and data structure
 * @arvec:indicates argument vector from main
 * Return: will be o if working and 1 if not(error)
 */
int shell_hsh(data_sh *data, char **arvec)
{
	ssize_t x = 0;
	int bltin = 0;

	while (x != -1 && bltin != -2)
	{
		erase_data(data);
		if (associate(data))
			put_string("$ ");
		_putschar_e(FLUSH_THE_BUFFER);
		x = fetch_input(data);
		if (x != -1)
		{
			set_data(data, arvec);
			bltin = detect_builtin(data);
			if (bltin == -1)
				detect_command(data);
		}
		else if (associate(data))
			put_character('\n');
		free_data(data, 0);
	}
	note_hist(data);
	free_data(data, 1);
	if (!associate(data) && data->condition)
		exit(data->condition);
	if (bltin == -2)
	{
		if (data->int_error == -1)
			exit(data->condition);
		exit(data->int_error);
	}
	return (bltin);
}

/**
 * detect_builtin - function will find a builtin command
 * @data: the param and return data structure
 * Return: will be -1 if builtin is not detected
 *         and 0 if builtin is successfully executed
 *         will be 1 if builtin not executed
 *         and 2 if builtin hints exit()
 */

int detect_builtin(data_sh *data)
{
	int x, bltin = -1;
	built_already_table bltinTbl[] = {
		{"exit", the_exit},
		{"envir", the_envir},
		{"help", the_help},
		{"histo_node", the_hist},
		{"setenv", the_set_envir},
		{"unsetenv", the_unset_envir},
		{"cd", the_cd},
		{"otherwise", the_otherwise},
		{NULL, NULL}
	};

	for (x = 0; bltinTbl[x].group; x++)
		if (the_string_compare(data->argvec[0], bltinTbl[x].group) == 0)
		{
			data->line_add++;
			bltin = bltinTbl[x].function(data);
			break;
		}
	return (bltin);
}

/**
 * detect_command - function finds command in path
 * @data: the param and data structure
 * Return: should be void
 */
void detect_command(data_sh *data)
{
	char *trail = NULL;
	int x, y;

	data->trail = data->argvec[0];
	if (data->line_add_symbol == 1)
	{
		data->line_add++;
		data->line_add_symbol = 0;
	}
	for (x = 0, y = 0; data->argument[x]; x++)
		if (!the_dlm(data->argument[x], "\t\n"))
			y++;
	if (!y)
		return;

	trail = look_for_path(data, get_envir(data, "PATH="), data->argvec[0]);
	if (trail)
	{
		data->trail = trail;
		split_command(data);
	}
	else
	{
		if ((associate(data) || get_envir(data, "PATH=")
					|| data->argvec[0][0] == '/') && the_command(data, data->argvec[0]))
			split_command(data);
		else if (*(data->argument) != '\n')
		{
			data->condition = 127;
			output_error(data, "not found\n");
		}
	}
}

/**
 * split_command - function forks an executable thread to run a command
 * @data: the param and data structure
 * Return: should return void
 */
void split_command(data_sh *data)
{
	pid_t baby_pid;

	baby_pid = fork();
	if (baby_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (baby_pid == 0)
	{
		if (execve(data->trail, data->argvec, fetch_envir(data)) == -1)
		{
			free_data(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(data->condition));
		if (WIFEXITED(data->condition))
		{
			data->condition = WEXITSTATUS(data->condition);
			if (data->condition == 126)
				output_error(data, "Permission Denied\n");
		}
	}
}
