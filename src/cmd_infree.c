
#include "minishell.h"

void    init_cmd(char *str, t_cmd *tmp)
{
    int     i;
    int     j;

    i = 0;
    j = 0;
    while (str[i])
    {
        while (str[i] && str[i] == ' ')
            i++;
        j++;
        i++;
    }
    tmp->argc = 0;
    tmp->argv = (char **)malloc(sizeof(char *) * (j + 1));
    tmp->pipe = 0;
    tmp->redirection = 0;
    tmp->quote = 0;
    tmp->fd[0] = 0;
    tmp->fd[1] = 0;
    tmp->next = NULL;
}

void    free_cmd(t_cmd *tmp) //env의 free와 같은 형식
{
    t_cmd   *del;
    int     i;

    i = 0;
    while (tmp)
    {
        del = tmp;
        tmp = tmp->next;
        // free(del->argv[0]);
        i = 0;
        while (del->argv[i])
        {
            free(del->argv[i]);
            i++;
        }
        free(del);
    }
    free(tmp);
}

void   new_init(char *str, t_cmd *tmp)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < ft_strlen(str))
    {
        while (str[i] && str[i] == ' ')
            i++;
        if (str[i] == '\'')
        {
            i++;
            while (str[i] && str[i] != '\'')
                i++;
            i++;
            j++;
            continue ;
        }
        else if (str[i] == '\"')
        {
            i++;
            while (str[i] && str[i] != '\"')
                i++;
            i++;
            j++;
            continue ;
        }
        while (str[i] && str[i] != ' ')
            i++;
        j++;
        i++;
    }
    tmp->argv = (char **)malloc(sizeof(char *) * (j + 1));
}
