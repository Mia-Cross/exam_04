#include "microshell.h"

int next_occur(char *c, char **tab, int index)
{
    if (index >= tab_len(tab))
        return (tab_len(tab));
    while (tab && tab[index] && strcmp(tab[index], c))
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