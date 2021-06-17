#include "microshell.h"

void ft_cd(char **arg)
{
    if (!arg[1] || arg[2])
        print_error_and_exit("error: cd: bad arguments\n");
    // write(1, arg[0], strlen(av[2]));
    if ((chdir(arg[1])) == -1)
    {
        ft_putstr_fd(2, "error: cd: cannot change directory to ");
        ft_putstr_fd(2, arg[1]);
        ft_putstr_fd(2, "\n");
        // print_error_and_exit("\n");
    }
    free(arg);
}

void simple_exec(char **args, char **env)
{
    pid_t pid;

    printf("SIMPLE EXEC -> \n");
    for (int i = 0; args[i]; i++)
        printf("ARG[%d] = |%s|\n", i, args[i]);
    if (args && !strcmp(args[0], "cd"))
    {
        ft_cd(args);
        return ;
    }
    if ((pid = fork()) == -1)
        print_error_and_exit("error: fatal\n");
    if (pid == 0)
    {
        if ((execve(args[0], args, env)) == -1)
        {
            ft_putstr_fd(2, "error: cannot execute ");
            ft_putstr_fd(2, args[0]);
            ft_putstr_fd(2, "\n");
            // print_error_and_exit("\n");
        }
        exit(0);
    }
    else
    {
        write(1, "hm", 2);
        waitpid(pid, NULL, 0);
        write(1, "-ok", 3);
        kill(pid, SIGTERM);
        // free(args);
    }
}

void execute_pipe(char **lhs, char **rhs, char **env)
{
    int pipefd[2];
    pid_t pid;
    // pid_t rhs_pid;

    if ((pipe(pipefd)) == -1 || (pid = fork()) == -1)
        print_error_and_exit("error: fatal\n");
    if (pid == 0)
    {
        // close(pipefd[RD_END]);
        dup2(pipefd[WR_END], STDIN_FILENO);
        // simple_exec(lhs, env);
        if ((execve(lhs[0], lhs, env)) == -1)
        {
            ft_putstr_fd(2, "error: cannot execute ");
            ft_putstr_fd(2, lhs[0]);
            ft_putstr_fd(2, "\n");
            // print_error_and_exit("\n");
        }
        exit (0);
        // printf("PIPE_FD[READ] = %d | PIPE_FD[WRITE] = %d\n", pipefd[RD_END], pipefd[WR_END]);
        // printf("FD = %d | STDIN = %d\n", *fd, STDIN_FILENO);
        // close(pipefd[RD_END]);
        // dup2(*fd, STDIN_FILENO);
        // printf("FD = %d | STDIN = %d\n", *fd, STDIN_FILENO);
        // // if ((next_pipe(args, 0)) > 0)
        //     dup2(pipefd[WR_END], STDOUT_FILENO);
        // printf("PIPE_FD[READ] = %d | PIPE_FD[WRITE] = %d\n", pipefd[RD_END], pipefd[WR_END]);
        // close(pipefd[WR_END]);
        // simple_exec(args, env);
        // exit (0);
    }
    if ((pid = fork()) == -1)
        print_error_and_exit("error: fatal\n");
    if (pid == 0)
    {
        close(pipefd[WR_END]);
        dup2(pipefd[RD_END], STDIN_FILENO);
        // simple_exec(rhs, env);
        if ((execve(rhs[0], rhs, env)) == -1)
        {
            ft_putstr_fd(2, "error: cannot execute ");
            ft_putstr_fd(2, rhs[0]);
            ft_putstr_fd(2, "\n");
            // print_error_and_exit("\n");
        }
        exit(0);
    }
    if (pid)
    {
        close(pipefd[RD_END]);
        close(pipefd[WR_END]);
        waitpid(pid, NULL, 0);
        // waitpid(rhs_pid, NULL, 0);
        free(lhs);
        free(rhs);

        // close(pipefd[WR_END]);
        // waitpid(pid, NULL, 0);
        // kill(pid, SIGTERM);
        // // if ((next_pipe(args, 0)) > 0)
        // *fd = pipefd[RD_END];
        // // dup2(*fd, pipefd[RD_END]);
        // free(args);
    }
}

void execute_command(int nb_args, char **args, char **env)
{
    int i = 0;
    int last = 0;
    // int fd = 0;

    while (args && i < nb_args)
    {
        // printf("arg = |%s|, bool = %d\n", args[i], strcmp(args[i], "|"));
        if (!strcmp(args[i], "|"))
        {
            write(1, "lets do a pipe\n", 15);
            execute_pipe(sub_str_tab(args, last, i), sub_str_tab(args, i + 1, nb_args), env);
            last = i + 1;
        }
        i++;
    }
    printf("last = %d\n", last);
    if (last == 0)
        simple_exec(args, env);
    // else
    //     execute_pipe(sub_str_tab(args, last, i), &fd, env);
    free(args);
}

int main(int ac, char **av, char **env)
{
    int i = 0;
    int last = 1;

    if (ac < 2)
        return (1);
    while (++i < ac)
    {
        // printf("arg = |%s|\n", av[i]);
        if (!strcmp(av[i], ";"))
        {
            execute_command(i - last, sub_str_tab(av, last, i), env);
            last = i + 1;
        }
    }
    execute_command(i - last, sub_str_tab(av, last, i), env);
    return (0);
}