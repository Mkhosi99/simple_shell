#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/**** reading and writing buffers ****/
#define READ_THE_BUFFER_SIZE 1024
#define WRITE_THE_BUFFER_SIZE 1024
#define FLUSH_THE_BUFFER -1

/**** To chain the commands ****/
#define COMMAND_NORMAL	0
#define COMMAND_OR	1
#define COMMAND_AND	2
#define COMMAND_CHAIN	3

/**** To convert the number ****/
#define CNVRT_LOWERCASE	1
#define CNVRT_UNSIGNED	2

/**** using getline function ****/
#define READ_GETLINE	0
#define STRNG_TOKENIZE	0

#define FILE_HISTORY	".the_shell_history"
#define MAXIMUM_HISTORY	4096

extern char **environment;

/**
 * struct list_string - The singly linked list
 * @number: Number field
 * @string: The string
 * @nextNode: Pointer to the next node
 */
typedef struct list_string
{
	int int_num;
	char *string;
	struct list_string *nextNode;
} list_sh;

/**
 * struct pass_in_data - Has the arguements to pass in the function, insuring
 *                       the prototype for pointer struct function
 * @argument: The string included from getline which has the arguments
 * @argvec: The array of strings from argument
 * @trail: The string path for the command
 * @argcount: The arguments counted in function
 * @line_add: The counted errors
 * @int_error: The error code
 * @line_add_symbol: If included, input should be added
 * @fle_name: The file name of the program
 * @envir: The linked list copy of environment
 * @environment: The modified custom copy from envir
 * @histo_node: The node containing the history
 * @otherwise: The alias node aka otherwise
 * @alter_environ: Used if the environment was changed or altered
 * @condition: Returns the status of the last executed command
 * @command_buffer: The pointer address, used if chaining happens
 * @buffer_type_command: The command type (||), (&&), (;)
 * @assess_fle_descrip: The file description that will read line input
 * @add_up_histo: Counts the history line number
 */
typedef struct pass_in_data
{
	char *argument;
	char **argvec;
	char *trail;
	char **environment;
	char *fle_name;
	char **command_buffer;
	int buffer_type_command;
	int assess_fle_descrip;
	int add_up_histo;
	int argcount;
	unsigned int line_add;
	int int_error;
	int line_add_symbol;
	int alter_environ;
	int condition;
	list_sh *envir;
	list_sh *histo_node;
	list_sh *otherwise;
} data_sh;

#define DATA_START \
{NULL, NULL, NULL, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL,NULL, 0, 0, NULL, \
	0, 0, 0,}

/**
 * struct built_already - Hads the builtin string and the functions related
 * @group: The command symbol that is builtin
 * @function: Indicates the function
 */
typedef struct built_already
{
	char *group;
	int (*function)(data_sh *);
} built_already_table;

/**** ascii_to_int.c ****/
int associate(data_sh *);
int the_dlm(char, char *);
int the_alphabet(int);
int ascii_to_int(char *);

/**** handle_errors.c ****/
void _puts_e(char *);
int _putschar_e(char);
int _puts_fle_descrip(char *string, int fle_descrip);
int _put_fle_descrip(char a, int fle_descrip);

/**** handle_history.c ****/
char *fetch_hist_fle(data_sh *data);
int note_hist(data_sh *data);
int look_thru_hist(data_sh *data);
int construct_hist_list(data_sh *data, char *buffer, int countline);
int renumb_hist(data_sh *data); /* renumbers history */

/**** handle_memory.c ****/
int makefree(void **);

/**** implement_builtin.c ****/
int the_exit(data_sh *);
int the_cd(data_sh *);
int the_help(data_sh *);

/**** implement_builtin1.c ****/
int the_hist(data_sh *);
int otherwise(data_sh *); /* alias */

/**** fetch_line.c ****/
ssize_t fetch_input(data_sh *);
int fetch_line(data_sh *, char **, size_t *);
void int_handle(int);

/**** fetch_data.c ****/
void erase_data(data_sh *);
void set_data(data_sh *, char **);
void free_data(data_sh *, int);

/**** fetch_envir.c ****/
char **fetch_envir(data_sh *);
int unset_envir(data_sh *, char *);
int set_envir(data_sh *, char *, char *);

/**** environment.c ****/
char *get_envir(data_sh *, const char *);
int the_envir(data_sh *);
int the_set_envir(data_sh *);
int the_unset_envir(data_sh *);
int occupy_envir_list(data_sh *);

/**** handle_lists.c ****/
list_sh *attach_node(list_sh **, const char *, int);
list_sh *attach_node_at_end(list_sh **, const char *, int);
size_t output_list_string(const list_sh *);
int remove_node_at_indicator(list_sh **, unsigned int);
void frees_the_list(list_sh **);

/**** handle_lists1.c ****/
size_t lenth_of_list(const list_sh *);
char **convert_list_to_strings(list_sh);
size_t output_list(const list_sh *);
list_sh *node_starting(list_sh *, char *, char);
ssize_t fetch_node_indicator(list_sh *, list_sh);

/**** variables.c ****/
int the_chain(data_sh *, char *, size_t *);
void look_at_chain(data_sh *, char *, size_t *, size_t, size_t);
int restore_otherwise(data_sh *); /* alias */
int restore_variables(data_sh);
int restore_string(char **, char *);

/**** handle_errors1.c ****/
int ascii_to_int_err(char *);
void output_error(data_sh *, char *);
int output_d_sh(int, int);
char *transform_number(long int, int, int);
void eliminate_comments(char *);

/**** shell_loop.c ****/
int shell_hsh(data_sh *, char **);
int detect_builtin(data_sh *);
void detect_command(data_sh *);
void split_command(info_ *);

/**** parsing.c ****/
int the_command(data_sh *, char *);
char *matching_character(char *, int, int);
char *look_for_path(data_sh *, char *, char *);

/**** loop_the_hsh.c ****/
int loop_the_hsh(char **);

/**** the_strings.c ****/
int the_string_lenth(char *);
int the_string_compare(char *, char *);
char *begins_with(const char *, const char *);
char *concatenate_the_strings(char *, char *);

/**** the_strings1.c ****/
char *copy_the_string(char *, char *);
char *duplicate_the_string(const char *);
void put_string(char *);
int put_character(char);

/**** the_exits.c ****/
char *copy_the_string(char *, char *, int);
char *concatenate_the_strings(char *, char *, int);
char *the_string_character(char *, char);

/**** split_string.c (aka tokenize) ****/
char **string_tokenize1(char *, char *);
char **string_tokenize2(char *, char);

/**** resize_memory.c ****/
char *set_block_memory(char *, char, unsigned int);
void free_the_memory(char **);
void *resize_mem(void *, unsigned int, unsigned int);

#endif
