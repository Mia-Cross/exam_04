#ifndef MICROSHELL_H
# define MICROSHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#define RD_END 0
#define WR_END 1

char *tab_to_str(char **tab, int nb_line);
char **split_to_char(char *str, char c);
int ft_strlen(char *str);
void ft_putstr_fd(int fd, char *str);
int ft_strchr_from(char *str, char c, int start);
void print_error_and_exit(char *str);
void remove_quotes(char **line);
int is_separator(char *str, int index);
int next_separator(char *str, int index);

// int		exec_child_pipe(int pipefd[2], int *fd, int i)
// {
// 	close(pipefd[RD_END]);
// 	data->line = ft_strdup(data->pipe[i]);
// 	dup2(*fd, STDIN_FILENO);
// 	if (data->pipe[i + 1])
// 		dup2(pipefd[WR_END], STDOUT_FILENO);
// 	close(pipefd[WR_END]);
// 	exec_line(data);
// }

// void		exec_pipe(int i, int fd, pid_t pid)
// {
// 	int		pipefd[2];

// 	while (data->pipe[i])
// 	{
// 		if (pipe(pipefd) == -1 || (pid = fork()) == -1)
// 			return (ft_putendl_fd(strerror(errno), 2));
// 		else if (pid == 0)
// 			exit(exec_child_pipe(data, pipefd, &fd, i));
// 		else
// 		{
// 			close(pipefd[WR_END]);
// 			waitpid(pid, &data->status, 0);
// 			kill(pid, SIGTERM);
// 			if (data->pipe[i + 1])
// 				fd = pipefd[RD_END];
// 			i++;
// 		}
//     }
// }

#endif