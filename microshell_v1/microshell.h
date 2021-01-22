#ifndef MICROSHELL_H
# define MICROSHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#define RD_END 0
#define WR_END 1

char *tab_to_str(char **tab, int nb_line);
char **split_to_char(char *str, char c);
int ft_strlen(char *str);
void ft_putstr_fd(int fd, char *str);
int ft_strchr_from(char *str, char c, int start);
void print_error_and_exit(char *str);
void remove_quotes(char **line);

#endif