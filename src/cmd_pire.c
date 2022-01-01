
#include "minishell.h"

int check_pipe(t_cmd *tmp)
{
    int i;

    i = 1;
    while (tmp->argv[i])
    {
        if (tmp->argv[i][0] == '|')
            return (1);
        else
            i++;
    }
    return (0);
}

int check_redi(char *str)// <은1 <<는2 >는3 >>는4
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '<')
        {
            if (str[i + 1] == ' ')
                return (1);
            else if (str[i + 1] == '<')
                return (2);
        }
        else if (str[i] == '>')
        {
            if (str[i + 1] == ' ')
                return (3);
            else if (str[i + 1] == '>')
                return (4);
        }
        i++;
    }
    return (0);
}
