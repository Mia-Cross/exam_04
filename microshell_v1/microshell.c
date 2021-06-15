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
        print_error_and_exit("\n");
    }
}

void simple_exec(char *cmd, char **av, char **env)
{
    pid_t pid;
    char **cmd_words;
    (void)av;

    printf("%s\n", cmd);
    cmd_words = split_to_char(cmd, ' ');
    if (strcmp(cmd_words[0], "cd") && ft_strlen(cmd_words[0]) == 2)
        return (ft_cd(cmd_words));
    if ((pid = fork()) == -1)
        print_error_and_exit("error: fatal\n");
    if (pid == 0)
    {
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
            printf("Pipe[%d] = |%s|\n", i, pipes[i]);
            if ((pid = fork()) == -1 || (pipe(pipefd)) == -1)
                print_error_and_exit("error: fatal\n");
            if (pid == 0)
            {
                close(pipefd[RD_END]);
                close(pipefd[WR_END]);
                simple_exec(cmd, av, env);
                exit (0);
            }
            else
            {
                close(pipefd[WR_END]);
                waitpid(pid, NULL, 0);
                kill(pid, SIGTERM);
                i++;
            }
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
    input = tab_to_str(av, ac);
    // remove_quotes(&input);
    // write(1, "#", 2);
    cmds = split_to_char(input, ';');
    i = 0;
    while (cmds && cmds[i])
        execute_command(cmds[i++], av, env);
    return (0);
}