# include "microshell.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str && str[i])
        i++;
    return (i);
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


