#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <stdio.h>

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void ft_putstrfd(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
}

void fatal_error(void)
{
	ft_putstrfd(2, "error: fatal\n");
	exit(1);
}

int	exec_cd(char **av)
{
	int i;

	i = 0;
	while (av[i] && strcmp(av[i], ";"))
		i++;
	if (i != 2)
	{
		ft_putstrfd(2, "error: cd: bad arguments\n");
	}
	else if (chdir(av[1]) == -1)
	{
		ft_putstrfd(2, "error: cd: cannot change directory to ");
		ft_putstrfd(2, av[1]);
		ft_putstrfd(2,"\n");
	}
	return (0);
}

char **get_arg(char **av)
{
	char **out;
	int i;
	int j;

	j = 0;
	i = 0;
	while (av[i] && strcmp(av[i], "|") && strcmp(av[i], ";"))
		i++;
	if (!(out = malloc((i + 1) * sizeof(char*))))
		fatal_error();
	while (j < i)
	{
		out[j] = av[j];
		j++;
	}
	out[j] = 0;
	return (out);
}

int check_pipe(char **av)
{
	int i;

	i = 0;
	while (av[i] && strcmp(av[i], ";"))
	{
		if(!strcmp(av[i], "|"))
			return (i);
		i++;
	}
	return (0);
}

int	exec_other(char **av, char **env, int p, int pipefd[2])
{
	pid_t pid;
	int status;
	char **arg;
	int buffd[2];

	buffd[0] = pipefd[0];
	if (!p || check_pipe(av))
		pipe(pipefd);
	if ((pid = fork()) == -1)
		fatal_error();
	if (pid == 0)
	{
		if (p || check_pipe(av))
		{
			dup2(buffd[0], 0);
			if (p)
				close(pipefd[0]);
			dup2(pipefd[1], 1);
		}
		arg = get_arg(&av[0]);
		if (execve(av[0], arg, env) == -1)
		{
			ft_putstrfd(2,"error: cannot execute ");
			ft_putstrfd(2, av[0]);
			ft_putstrfd(2, "\n");
			free(arg);
			exit(1);
		}
		exit(0);
	}
	else
	{
		waitpid(-1, &status, 0);
		close(pipefd[1]);
		close(buffd[0]);
		if(check_pipe(av))
			exec_other(&av[check_pipe(av) + 1],env, 1, pipefd);
		else
			close(pipefd[0]);
	}
	return (0);
}

char **remake_av(char **av, int ac)
{
	char **out;
	int i;
	i = 0;

	if (!(out = malloc((ac + 1) * sizeof(char *))))
		fatal_error();
	while (i < ac)
	{
		out[i] = av[i];
		i++;
	}
	out[i] = 0;
	return (out);
}

int main(int ac, char **av, char **env)
{
	(void)env;
	int i;
	int fd[2];
	av = remake_av(av, ac);
	i = 1;
	while (i < ac)
	{
		while (av[i] && !strcmp(av[i], ";"))
			i++;
		if (i >= ac)
			break ;
		if (!strcmp(av[i], "cd"))
			exec_cd(&av[i]);
		else
			exec_other(&av[i], env, 0, fd);
		fd[0] = -1;
		fd[1] = -1;
		while (av[i] && strcmp(av[i], ";"))
			i++;
		i++;
	}
	return (0);
}
