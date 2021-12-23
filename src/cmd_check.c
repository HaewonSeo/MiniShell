
#include "minishell.h"

int check_cmd(t_cmd *tmp)
{
    int i;
    int j;
    int k;

    i = 0;
    j = 0;
    k = 0;
    while (tmp->argv[j])
        j++;
    while (i < j)
    {
        if (!ft_strcmp(tmp->argv[i], "cd") || !ft_strcmp(tmp->argv[i], "echo")
	    || !ft_strcmp(tmp->argv[i], "pwd") || !ft_strcmp(tmp->argv[i], "env")
	    || !ft_strcmp(tmp->argv[i], "export") || !ft_strcmp(tmp->argv[i], "export")
	    || !ft_strcmp(tmp->argv[i], "unset") || !ft_strcmp(tmp->argv[i], "exit"))
            k++;
        if (tmp->pipe == 0)
            break ;
        else
        {
            while (ft_strcmp(tmp->argv[i], "-"))
                i++;
        }
    }
	return (k);
}

int check_quote(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\'')
            return (1);
        else if (str[i] == '\"')
            return (2);
        i++;
    }
    return (0);
}

int     where_pire(char *str)
{
    int i;
    
    i = 0;
    while (str[i])
    {
        if (str[i] == '|')
            return (i + 1);
        else if (str[i] == '>')
        {
            if (str[i + 1] == '>')
                return (i + 2);
            else if (str[i + 1] == ' ')
                return (i + 1);
        }
        else if (str[i] == '<')
        {
            if (str[i + 1] == '<')
                return (i + 2);
            else if (str[i + 1] == ' ')
                return (i + 1);
        }
        i++;
    }
    return (-1);
}

int where_quote(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\'')
            return (i);
        if (str[i] == '\"')
            return (i);
        i++;
    }
    return (-1);
}

void    check_right(char *str) // | < << > >> " '
{
    ch_right_quote(str);
    ch_right_pipe(str);
    ch_right_redi(str);
}
