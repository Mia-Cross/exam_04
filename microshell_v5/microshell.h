#ifndef MICROSHELL_H
# define MICROSHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# define READ 0
# define WRITE 1

int tab_len(char **tab);
void ft_putstr_fd(int fd, char *str);
int next_occur(char *c, char **tab, int index);
int nb_segments(char *c, char **tab);
char **sub_tab(char **tab, int begin, int end);

#endif