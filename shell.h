#ifndef SHELL_H_
#define SHELL_H_

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>
#include <signal.h>

extern char **environ;

void not_detected(char *argve, int dash, char *comnd);
void invalid_numb(char *argve, int dash, char *numbr);
char *fetch_envir(char *env_label);
void output_envir(char **);
void error_perm(char *argve, int dash, char *comnd);

void mk_itoa(int x);
int mk_atoi(const char *str);

void mk_cwritechar(char a);
void mk_swrites(char *strng);
void mk_writechar(char a);
void mk_writes(char *strng);

char **split_str(char *strng);
char *fetch_comnd(char *comnd);
char *fetch_envir(char *envir_label);
void release_tkn(char **tkn);
void ext_sh(char **tkn, char **argve, int dash, int condition, char *bufr);
int comnd_envir(char **tkn, char **envir, char *bufr);
char **fetch_tkn(char **bufr, int condition);
int exec_comnd(char **tkn, char **argvev, int dash, char **envir);


int mk_strnglenth(const char *a);
char *mk_strngcopy( char *end, char *start);
char *mk_strngcncat(char *end, char *start);
int mk_strngcmpre(char *str1, char *str2);

#endif
