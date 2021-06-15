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
    // printf("-->> LINE : \"%s\"\n", str);
    return (str);
}

int get_nb_words(char *str, char c)
{
    int i;
    int count;

    i = 0;
    count = 1;
    while (str && str[i])
    {
        if (str[i] == c && is_separator(str, i))
            count++;
        i++;
    }
    return (count);
}

char **split_to_char(char *str, char c)
{
    // int i;
    int j;
    // int i_max;
    int j_max;
    // int len;
    int next = 0;
    int prev = 0;
    char **tab;

    j = 0;
    j_max =  get_nb_words(str, c);
    printf("FOR \'%c\', count = %d\n", c,j_max);
    if (!(tab = (char **)malloc(sizeof(char *) * (j_max + 1))))
        return (NULL);
    while (str && *str && j < j_max)
    {
        next = next_separator(str, ++prev);
        // len = 0;
        // while (str[len] && str[len] == c)
        //     str++;
        // while (str[len] && str[len] != c && is_separator(str, len))
        //     len++;
        // if (!(tab[j] = (char *)malloc(sizeof(char) * (len + 1))))
        if (!(tab[j] = (char *)malloc(sizeof(char) * (next - prev + 2))))
            return (NULL);
        // i = 0;
        // while (i < len)
        //     tab[j][i++] = *str++;
        while (++prev < next)
            tab[j][prev] = *str++;
        tab[j][prev] = 0;
        j++;
        prev = next;
        printf("just stored = %s\n", tab[j - 1]);
    }
    tab[j] = NULL;
    return (tab);
}

void remove_quotes(char **line)
{
  //  int nb;
    int occur;

 //   nb = 0;
    occur = 0;
    // while ( (occur = ft_strchr_from(*line, '"', occur)) >= 0 )
    //     nb++;
    // if (nb % 2)
    //     exit (1);
    while ( (occur = ft_strchr_from(*line, '"', 0)) >= 0 )
    {
        //write(1, "yo", 2);
        while (*line && *line[occur + 1])
        {
            *line[occur] = *line[occur + 1];
            occur++;
        }
        *line[occur] = 0;
    }
}