#include "microshell.h"

void ft_putstr_fd(int fd, char *str)
{
    int i = 0;
    while (str && str[i])
        write(fd, &str[i++], 1);
}

int tab_len(char **tab)
{
    int i = 0;
    while (tab && tab[i])
        i++;
    return (i);
}

int next_occur(char *c, char **tab, int index)
{
    if (index >= tab_len(tab))
        return (tab_len(tab));
    while (tab && tab[index] && strcmp(tab[index], c))
        index++;
    return (index);
}

int nb_segments(char *c, char **tab)
{
    int count = 1;
    int i = 0;
    while (tab && tab[i + 1])
    {
        if (!strcmp(tab[i++], c))
            count++;
    }
    return (count);
}

char **sub_tab(char **tab, int begin, int end)
{
    char **sub;
    int i = 0;

    if (!(sub = (char **)malloc(sizeof(char *) * (end - begin + 1))))
        return (NULL);
    while (begin < end)
        sub[i++] = tab[begin++];
    sub[i] = 0;
    return (sub);
}