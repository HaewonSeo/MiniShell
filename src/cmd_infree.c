
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
    tmp->shell_var = 0;
    tmp->next = NULL;
    tmp->redir = (t_redir *)ft_calloc(1, sizeof(t_redir));///
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
        i = 0;
        while (del->argv[i])
        {
            free(del->argv[i]);
            i++;
        }
        if (del->redir->r)
            free(del->redir->r);
        if (del->redir->l)
            free(del->redir->l);
        if (del->redir->rr)
            free(del->redir->rr);
        if (del->redir->ll)
            free(del->redir->ll);
        free(del);
    }
    free(tmp);
}

void   new_init(char *str, t_cmd *tmp)
{
    int     i;
    int     j;
    char    c;

    i = 0;
    j = 0;
    while (i++ < ft_strlen(str))
    {
        while (str[i] && str[i] == ' ')
            i++;
        if (str[i] == '\'' || str[i] == '\"')
        {
            c = str[i];
            i++;
            while (str[i] && str[i] != c)
                i++;
            i++;
            j++;
            continue ;
        }
        while (str[i] && str[i] != ' ')
            i++;
        j++;
    }
    tmp->argv = (char **)malloc(sizeof(char *) * (j + 1));
}