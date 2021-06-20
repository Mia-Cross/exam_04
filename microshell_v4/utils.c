#include "microshell.h"

void ft_putstr_fd(int fd, char *str)
{
    int i = 0;

    while (str[i])
        write(fd, &str[i++], 1);
}

int tab_len(char **tab)
{
    int i = 0;

    while (tab[i])
        i++;
    return (i);
}

int nb_segments(char *c, char **tab)
{
    int i = 0;
    int count = 1;

    while (tab && tab[i + 1])
    {
        if (!strcmp(tab[i++], c))
            count++;
    }
    return (count);
}
