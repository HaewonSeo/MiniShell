
#include "minishell.h"

void    put_redirection(t_cmd *tmp)
{
    int i;

    i = 0;
    if (tmp->redirection == 0)
        return ;
    while (i < tmp->argc)
    {
        if (tmp->argv[i][0] == '<')
        {
            if (!tmp->argv[i][1])
                tmp->redir->l = tmp->argv[i + 1];
            else if (tmp->argv[i][1] == '<')
                tmp->redir->ll = tmp->argv[i + 1];
            i++;
        }
        if (tmp->argv[i][0] == '>')
        {
            if (!tmp->argv[i][1])
                tmp->redir->r = tmp->argv[i + 1];
            else if (tmp->argv[i][1] == '>')
                tmp->redir->rr = tmp->argv[i + 1];
            i++;
        }
        i++;
    }
}

int parsing_cmd_qu(char *str, t_cmd *tmp)
{
    int i;
    int j;
    int mid;

    i = 0;
    j = 0;
    new_init(str, tmp);
    while (i < ft_strlen(str))
    {
        while (str[i] && str[i] == ' ')
            i++;
        mid = i;
        if (str[i] == '\'')
        {
            i++;
            while (str[i] && str[i] != '\'')
                i++;
            tmp->argv[j] = ft_substr(str, mid + 1, i - mid - 1);
            i++;
            j++;
            continue ;
        }
        else if (str[i] == '\"')
        {
            i++;
            while (str[i] && str[i] != '\"')
                i++;
            tmp->argv[j] = ft_substr(str, mid + 1, i - mid - 1);
            i++;
            j++;
            continue ;
        }
        while (str[i] && str[i] != ' ')
            i++;
        tmp->argv[j] = ft_substr(str, mid, i - mid);
        j++;
        i++;
    }
    tmp->argv[j] = 0;
    return (j);
}

void    remove_redi(t_cmd *tmp)
{
    int     i;
    int     j;

    i = 0;
    j = tmp->argc;
    while (tmp->argv[i])
    {
        if (tmp->argv[i][0] == '<')
        {
            j = i;
            while (tmp->argv[j + 2])
            {
                tmp->argv[j] = tmp->argv[j + 2];
                j++;
            }
            tmp->argv[j] = NULL;
            i = 0;
            continue ;
        }
        if (tmp->argv[i][0] == '>')
        {
            j = i;
            while (tmp->argv[j + 2])
            {
                tmp->argv[j] = tmp->argv[j + 2];
                j++;
            }
            tmp->argv[j] = NULL;
            i = 0;
            continue ;
        }
        i++;
        tmp->argc = j;
    }
}

void    re_parsing_cmd(t_cmd *tmp, char *str)
{
    int     i;
    int     j;
    int     k;
    t_cmd   *new;

    i = 0;
    j = 0;
    new = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
    new->redir = (t_redir *)ft_calloc(1, sizeof(t_redir));
    new->quote = check_quote(str);
    while (tmp->argv[i])
    {
        if (tmp->argv[i][0] == '|')
            break ;
        i++;
    }
    k = i + 1;
    new->argv = (char **)malloc(sizeof(char *) * (tmp->argc - k + 1));
    new->argc = tmp->argc - k;
    tmp->argc = tmp->argc - new->argc - 1;
    while (tmp->argv[k])
        new->argv[j++] = tmp->argv[k++];
    new->argv[j] = 0;
    tmp->argv[i] = 0;
    new->pipe = check_pipe(new);
    k = where_pipe(str);
    new->redirection = check_redi(str + k);
    tmp->next = new;
    new->next = NULL;
    if (where_quote(str) > where_pipe(str))
        tmp->quote = 0;
    if (new->pipe > 0)
        re_parsing_cmd(new, str + k);
    put_redirection(new);
    remove_redi(new);
}

void    parsing_cmd(char *str, t_cmd **cur)
{
    int     i;
    int     j;
    int     k;
    int     mid;
    t_cmd   *tmp;

    j = 0;
    check_right(str);
    tmp = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
    k = check_cmd_env(str);
    if (k != -1)
        (*cur)->next = parsing_cmd_env(str);
    else
        k = 0;
    str = str + k;
    init_cmd(str, tmp);
    i = 0;
    tmp->quote = check_quote(str);
    while(tmp->quote == 0 && i < ft_strlen(str))
    {
        while (str[i] && str[i] == ' ')
            i++;
        mid = i;
        while (str[i] && str[i] != ' ')
            i++;
        tmp->argv[j] = ft_substr(str, mid, i - mid);
        j++;
        i++;
    }
    tmp->argv[j] = 0;
    if (tmp->quote != 0)
        j = parsing_cmd_qu(str, tmp);
    tmp->argc = j;
    tmp->pipe = check_pipe(tmp);
    tmp->redirection = check_redi(str);
    if (tmp->pipe == 1 && where_pipe(str) < where_redi(str))
        tmp->redirection = 0;
    if (k == 0)
        (*cur)->next = tmp;
    else
        (*cur)->next->next = tmp;
    if (where_quote(str) > where_pipe(str))
        tmp->quote = 0;
    if (tmp->pipe > 0)
        re_parsing_cmd(tmp, str);
    put_redirection(tmp);//
    remove_redi(tmp);//
    return ;
}
