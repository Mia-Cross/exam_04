#include "microshell.h"

void print_error(char *str)
{
    int i = 0;
    while (str && str[i])
        write(2, &str[i++], 1);
}

int next_occur(char *c, char **tab,  int index)
{
    while (tab && tab[index] && strcmp(c, tab[index]))
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

int nb_segments(char *c, char **tab)
{
    int i = 0;
    int count = 1;
    if (!tab || !tab[0])
        return 0;
    while (tab[i])
    {
        if (!strcmp(tab[i++], c))
            count++;
    }
    return count;
}