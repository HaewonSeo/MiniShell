
#include "minishell.h"

void    init_cmd(char *str, t_cmd *tmp)
{
    int     i;
    int     j;

    tmp = (t_cmd *)ft_calloc(1, sizeof(t_cmd));           // cmd node를 동적할당
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
    tmp->next = NULL;
    return (tmp);
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
        free(del->argv[0]);
        while (del->argv[i])
        {
            free(del->argv[i]);
            i++;
        }
        free(del);
    }
    free(tmp);
}
