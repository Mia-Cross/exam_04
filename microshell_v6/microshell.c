#include "microshell.h"
#include <stdio.h>

void ft_cd(char **av)
{
    if (!av[1] || av[2])
    {
        ft_putstr_fd(2, "error: cd: bad arguments\n");
        return;
    }
    if (chdir(av[1]) == -1)
    {
        ft_putstr_fd(2, "error: cd: cannot change directory to ");
        ft_putstr_fd(2, av[1]);
        ft_putstr_fd(2, "\n");
    }
}

void execute_pipe(char **av, char **env, int *fd, int last)
{
    int pipefd[2];
    pid_t pid;

    if (!strcmp(av[0], "cd"))
        return (ft_cd(av));
    if (pipe(pipefd) == -1 || (pid = fork()) == -1)
    {
        ft_putstr_fd(2, "error: fatal\n");
        exit(1);
    }
    if (pid == 0)
    {
        close(pipefd[READ]);
        dup2(*fd, STDIN_FILENO);
        if (!last)
            dup2(pipefd[WRITE], STDOUT_FILENO);
        if (execve(av[0], av, env) == -1)
        {
            ft_putstr_fd(2, "error: cannot execute ");
            ft_putstr_fd(2, av[0]);
            ft_putstr_fd(2, "\n");
        }
        close(pipefd[WRITE]);
    }
    else
    {
        close(pipefd[WRITE]);
        waitpid(pid, NULL, 0);
        kill(pid, SIGTERM);
        if (!last)
            dup2(pipefd[READ], *fd);
        close(pipefd[READ]);
    }
}

int main(int ac, char **av, char **env)
{
    char **cmds;
    char **pipes;
    int fd = 0;
    int last_cmd = 1;
    int last_pipe = 0;

    if (ac < 2)
        return (1);
    for (int i = 0; i < nb_segments(";", av); i++)
    {
        cmds = sub_tab(av, last_cmd, next_occur(";", av, last_cmd));
        last_pipe = 0;
        for (int j = 0; j < nb_segments("|", cmds); j++)
        {
            pipes = sub_tab(cmds, last_pipe, next_occur("|", cmds, last_pipe));
            if (j + 1 < nb_segments("|", cmds))
                execute_pipe(pipes, env, &fd, 0);
            else
                execute_pipe(pipes, env, &fd, 1);
            free(pipes);
            pipes = NULL;
            last_pipe = next_occur("|", cmds, last_pipe + 1) + 1;
        }
        free(cmds);
        cmds = NULL;
        last_cmd = next_occur(";", av, last_cmd + 1) + 1;
    }
    return (0);
}