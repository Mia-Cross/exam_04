# include "microshell.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str && str[i])
        i++;
    return (i);
}

int ft_tablen(char **tab)
{
    int i = 0;
    while (tab && tab[i])
        i++;
    return i;
}

void print_error_and_exit(char *str)
{
    write(2, str, ft_strlen(str));
    exit (1);
}

void ft_putstr_fd(int fd, char *str)
{
    int i;

    i = 0;
    while (str && str[i])
        write(fd, &str[i++], 1);
}

int nb_segments(char **av, char *str)
{
    int count = 1;

    for (int i = 0; av[i]; i++)
    {
        if (!strcmp(av[i], str))
            count++;
    }
    return (count) ;
}

