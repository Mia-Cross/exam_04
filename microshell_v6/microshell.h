#ifndef MICROSHELL_H
# define MICROSHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <string.h>

# define READ 0
# define WRITE 1

void ft_putstr_fd(int fd, char *str);
int tab_len(char **tab);
int nb_segments(char *c, char **tab);
int next_occur(char *c, char **tab,  int index);
char **sub_tab(char **tab, int begin, int end);

#endif