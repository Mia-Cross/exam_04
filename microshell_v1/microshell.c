#include "microshell.h"

void ft_cd(int ac, char **av)
{
    if (ac != 3)
        print_error_and_exit("error: cd: bad arguments\n");
    if ((chdir(av[2])) == -1)
    {
        ft_putstr_fd(2, "error: cd: cannot change directory to ");
        ft_putstr_fd(2, av[2]);
        print_error_and_exit("\n");
    }
}

void simple_exec(char *cmd, char **av, char **env)
{
    pid_t pid;
    char **cmd_words;
    (void)av;

    cmd_words = split_to_char(cmd, ' ');
    if ((pid = fork()) == -1)
        print_error_and_exit("error: fatal\n");
    if (pid == 0)
    {
    //    write(1, "hey", 3);
        int i = 0;
        while(cmd_words[i])
        {
            ft_putstr_fd(1, cmd_words[i++]);
            ft_putstr_fd(1, "\n");
        }
        if ((execve(cmd_words[0], cmd_words, env)) == -1)
        {
            ft_putstr_fd(2, "error: cannot execute ");
            ft_putstr_fd(2, cmd_words[0]);
            print_error_and_exit("\n");
        }
    }
    else
    {
        waitpid(pid, NULL, 0);
  //      write(1, "hm", 3);
    }
}

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

// 	data->status = 0;
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


void execute_command(char *cmd, char **av, char **env)
{
    char **pipes;
    int pipefd[2];
    pid_t pid;
    int i;

    if (ft_strchr_from(cmd, '|', 0) >= 0)
    {
        pipes = split_to_char(cmd, '|');
        i = 0;
        while (pipes[i])
        {
            if ((pid = fork()) == -1 || (pipe(pipefd)) == -1)
                print_error_and_exit("error: fatal\n");
            if (pid == 0)
            {
                //if (execve()
            }
            else
                waitpid(-1, NULL, 0);
        }
    }
    else
        simple_exec(cmd, av, env);
}

int main(int ac, char **av, char **env)
{
    char **cmds;
    char *input;
    int i;

    if (ac < 2)
        return (1);
    else if (!strcmp(av[1], "cd") && (ft_strlen(av[1])) == 2)
        ft_cd(ac, av);
    else
    {
        input = tab_to_str(av, ac);
        remove_quotes(&input);
       // write(1, "#", 2);
        cmds = split_to_char(input, ';');
        i = 0;
        while (cmds && cmds[i])
            execute_command(cmds[i++], av, env);
    }
    return (0);
}