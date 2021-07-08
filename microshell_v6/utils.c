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

int nb_segments(char *c, char **tab)
{
    int i = 0;
    int count = 1;
    if (!tab || !tab[0])   // very important to avoid segfaults
        return 0;
    while (tab && tab[i + 1])
    {
        if (!strcmp(c, tab[i++]))
            count++;
    }
    return (count);
}

int next_occur(char *c, char **tab,  int index)
{
    while (tab && index < tab_len(tab) && strcmp(c, tab[index]))
        index++;
    return (index);
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