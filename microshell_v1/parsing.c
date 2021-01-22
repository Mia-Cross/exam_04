#include "microshell.h"

char *tab_to_str(char **tab, int nb_line)
{
    int i;
    int j;
    int len;
    char *str;

    i = 0;
    len = 0;
    while (++i < nb_line)
        len += ft_strlen(tab[i]);
    if (!(str = (char *)malloc(sizeof(char) * len + 1)))
        return (NULL);
    str[len] = 0;
    i = 0;
    len = 0;
    while (++i < nb_line)
    {
        j = 0;
        while (tab[i] && tab[i][j])
            str[len++] = tab[i][j++];
    }
    return (str);
}

int get_nb_words(char *str, char c)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (str && str[i])
    {
        if (str[i] == c)
            count++;
    }
    return (count);
}

char **split_to_char(char *str, char c)
{
    int i;
    int j;
    int len;
    char **tab;

    j = 0;
    if (!(tab = (char **)malloc(sizeof(char *) * (get_nb_words(str, c) + 1))))
        return (NULL);
    while (str && *str)
    {
        len = 0;
        while (str && str[len] && str[len] != c)
            len++;
        if (!(tab[j] = (char *)malloc(sizeof(char) * (len + 1))))
            return (NULL);
        i = 0;
        while (i < len)
            tab[j][i++] = *str++;
        tab[j][len] = 0;
        j++;
    }
    tab[j] = NULL;
    return (tab);
}

void remove_quotes(char **line)
{
    int nb;
    int occur;

    nb = 0;
    occur = 0;
    // while ( (occur = ft_strchr_from(*line, '"', occur)) >= 0 )
    //     nb++;
    // if (nb % 2)
    //     exit (1);
    while ( (occur = ft_strchr_from(*line, '"', 0)) >= 0 )
    {
        while (*line && *line[occur + 1])
        {
            *line[occur] = *line[occur + 1];
            occur++;
        }
        *line[occur] = 0;
    }
}