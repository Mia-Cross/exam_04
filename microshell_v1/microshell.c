#include "microshell.h"

void ft_cd(int ac, char **av, char **env)
{
    if (ac != 3)
    {
        ft_putstr_fd(2, "error: cd: bad arguments\n");
        exit (1);
    }
    if ((chdir(av[2])) == -1)
    {
        ft_putstr_fd(2, "error: cd: cannot change directory to ");
        ft_putstr_fd(2, av[2]);
        ft_putstr_fd(2, "\n");
        exit (1);
    }
}

tatic int		exec_child_pipe(t_data *data, int pipefd[2], int *fd, int i)
{
	close(pipefd[RD_END]);
	data->line = ft_strdup(data->pipe[i]);
	dup2(*fd, STDIN_FILENO);
	if (data->pipe[i + 1])
		dup2(pipefd[WR_END], STDOUT_FILENO);
	close(pipefd[WR_END]);
	exec_line(data);
}

static void		exec_pipe(qint i, int fd, pid_t pid)
{
	int		pipefd[2];

	data->status = 0;
	while (data->pipe[i])
	{
		if (pipe(pipefd) == -1 || (pid = fork()) == -1)
			return (ft_putendl_fd(strerror(errno), 2));
		else if (pid == 0)
			exit(exec_child_pipe(data, pipefd, &fd, i));
		else
		{
			close(pipefd[WR_END]);
			waitpid(pid, &data->status, 0);
			kill(pid, SIGTERM);
			if (data->pipe[i + 1])
				fd = pipefd[RD_END];
			data->status = data->status == 32512 ? 127 : data->status;
			i++;
		}

void execute_command(char *cmd)
{
    char **pipes;
    pid_t pid;

    if (ft_strchr_from(cmd, '|', 0))
    {
        pipes = split_to_char(cmd, '|');
    }

    pid = fork();
    if (pid == 0)
    {
        if (execve()
    }
    else if (pid > 0)
        waitpid(-1, NULL, 0);
    else
        print_error_and_exit("error: fatal\n");
}

int main(int ac, char **av, char **env)
{
    char **cmds;
    char *input;
    int i;

    if (ac < 2)
        return (1);
    else if (strcmp(av[1], "cd" && ft_strlen(av[1]) == 2))
        ft_cd(ac, av, env);
    else
    {
        input = tab_to_str(av, ac);
        remove_quotes(&input);
        cmds = split_to_char(input, ';');
        i = 0;
        while (cmds && cmds[i])
            execute_command(cmds[i]);
    }
    return (0);
}