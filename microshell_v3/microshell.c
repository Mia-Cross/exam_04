#include "microshell.h"

void ft_cd(char **arg)
{
    if (!arg[1] || arg[2])
        print_error_and_exit("error: cd: bad arguments\n");
    if ((chdir(arg[1])) == -1)
    {
        ft_putstr_fd(2, "error: cd: cannot change directory to ");
        ft_putstr_fd(2, arg[1]);
        ft_putstr_fd(2, "\n");
    }
}

void execute_pipe(char **arg, char **env, int *fd, int last)
{
    int pipefd[2];
    pid_t pid;

    if (!arg || !arg[0])
        return ;
    if (!strcmp(arg[0], "cd"))
    {
        ft_cd(arg);
        return ;
    }
    if (pipe(pipefd) == -1 || (pid = fork()) == -1)
        print_error_and_exit("error: fatal\n");
    if (pid == 0)
    {
        close(pipefd[RD_END]);
        dup2(*fd, STDIN_FILENO);
        if (!last)
            dup2(pipefd[WR_END], STDOUT_FILENO);
        close(pipefd[WR_END]);
        if ((execve(arg[0], arg, env)) == -1)
        {
            ft_putstr_fd(2, "error: cannot execute ");
            ft_putstr_fd(2, arg[0]);
            ft_putstr_fd(2, "\n");
        }
    }
    else
    {
        close(pipefd[WR_END]);
        waitpid(pid, NULL, 0);
        kill(pid, SIGTERM);
        if (!last)
            dup2(pipefd[RD_END], *fd);
        close(pipefd[RD_END]);
    }
}

int main(int ac, char **av, char **env)
{
    int nb_cmds;
    int nb_pipes;
    int fd = 0;

    if (ac < 2)
        return (1);
    // system("lsof | wc -l");
    nb_cmds = nb_segments(av, ";");
    int last_cmd = 0;

    for (int i = 0; i < nb_cmds; i++)
    {
        ft_putstr_fd(2, "cmd\n");
        char **cmd_args = sub_str_tab(av, last_cmd + 1, next_occur(";", av, last_cmd));
        nb_pipes = nb_segments(cmd_args, "|");
        int last_pipe = 0;

        for (int j = 0; j < nb_pipes; j++)
        {
            char **pipe_args = sub_str_tab(cmd_args, last_pipe, next_occur("|", cmd_args, last_pipe));
            if (j + 1 < nb_pipes)
                execute_pipe(pipe_args, env, &fd, 0);
            else
                execute_pipe(pipe_args, env, &fd, 1);
            last_pipe = next_occur("|", cmd_args, last_pipe) + 1;
            free(pipe_args);
            pipe_args = NULL;
        }

        last_cmd = next_occur(";", av, last_cmd);
        free(cmd_args);
        cmd_args = NULL;
    }
    // system("lsof | wc -l");
    // ft_putstr_fd(2, "\n----\n");
    return (0);
}