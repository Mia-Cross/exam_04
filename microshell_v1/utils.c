# include "microshell.h"

void print_error_and_exit(char *str)
{
    ft_putstr_fd(2, str);
    exit (1);
}

int is_separator(char *str, int index)
{
    int i = 0;
    int nb_quotes = 0;

    while (str && str[i] && i < index)
    {
        if (str[i++] == '\"')
            nb_quotes++;
    }
    if (nb_quotes % 2)
        return (1);
    return (0);
}

int next_separator()
{
    while (is_separator())
    return (index du separteur)
}

int ft_strchr_from(char *str, char c, int start)
{
    int i;

    if (start < 0 && start > ft_strlen(str))
        return (-1);
    i = start;
    while (str && str[i])
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (-1);
}

void ft_putstr_fd(int fd, char *str)
{
    int i;

    i = 0;
    while (str && str[i])
        write(fd, &str[i++], 1);
}

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str && str[i])
        i++;
    return (i);
}

