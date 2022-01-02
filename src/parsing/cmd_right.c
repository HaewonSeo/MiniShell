
#include "minishell.h"

void    printf_error(int i)
{
    if (i == 1)
    {
        printf("error : quote error\n");
        return ;
    }
    if (i == 2)
    {
        printf("error : parse error near `|'\n");
        return ;
    }
    if (i == 3)
    {
        printf("error : parse error near `\\n'\n");
        return ;
    }
}

void    ch_right_redi_2(char *str, int i)
{
    while (str[i] && str[i] == ' ')
    {
                i++;
            if (str[i] == '|')
                printf_error(3);
            if (str[i] == '>' || str[i] == '<')
                printf_error(3);
            if (!str[i])
                printf_error(3);
    }
}

void    ch_right_redi(char *str)
{
    int i;

    i = 0;
     while (str[i])
    {
        if (str[i] == '>')
        {
            i++;
            if (str[i] == '>')
                i++;
            ch_right_redi_2(str, i);
        }
        if (str[i] == '<')
        {
            i++;
            if (str[i] == '<')
                i++;
            ch_right_redi_2(str, i);
        }
        i++;
    }
}

void    ch_right_pipe(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '|')
        {
            i++;
            while (str[i] && str[i] == ' ')
                i++;
            if (str[i] == '|')
                printf_error(2);
            if (str[i] == '>' || str[i] == '<')
                printf_error(2);
            if (!str[i])
                printf_error(2);
        }
        i++;
    }
}

void    ch_right_quote(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\'')
        {
            i++;
            while (str[i] && str[i] != '\'')
                i++;
            if (i >= ft_strlen(str))
                printf_error(1);
        }
        if (str[i] == '\"')
        {
            i++;
            while (str[i] && str[i] != '\"')
                i++;
            if (i >= ft_strlen(str))
                printf_error(1);
        }
        i++;
    }
}
