
#include "minishell.h"

int parsing_cmd_qu(char *str, t_cmd *tmp)
{
    int     i;
    int     j;
    int     mid;

    i = 0;
    j = 0;
    new_init(str, tmp);
    while (i++ < ft_strlen(str))
    {
        while (str[i] && str[i] == ' ')
            i++;
        mid = i;
        if (str[i] == '\'' || str[i] == '\"')
        {
            i = check_i(str, tmp, i, j, mid);//
            j++;
            continue ;
        }
        while (str[i] && str[i] != ' ')
            i++;
        tmp->argv[j] = ft_substr(str, mid, i - mid);
        j++;
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
        if (tmp->argv[i][0] == '<' || tmp->argv[i][0] == '>')
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

void    re_parsing_cmd_env(t_cmd *tmp)
{
    int i;

    i = 0;
    while (tmp->argv[i])
    {
        if (tmp->argv[i][0] == '|' && !tmp->argv[i][1])
            break ;
        i++;
    }
    tmp->argc = i;
    tmp->argv[i] = 0;
}

void    re_parsing_cmd(t_cmd *tmp, char *str)
{
    int     i;
    int     k;
    t_cmd   *new;

    i = 0;
    if (check_cmd_env(str) > 0 && ft_strlen(str + check_cmd_env(str)) == 0)
    {
        tmp->next = parsing_cmd_env(str);
        re_parsing_cmd_env(tmp);
        return ;
    }
    new = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
    new->redir = (t_redir *)ft_calloc(1, sizeof(t_redir));
    new->quote = check_quote(str);
    k = argv_pipe(tmp) + 1;
    new->argv = (char **)malloc(sizeof(char *) * (tmp->argc - k + 1));
    new->argc = tmp->argc - k;
    tmp->argc = tmp->argc - new->argc - 1;
    while (tmp->argv[k])
        new->argv[i++] = tmp->argv[k++];
    new->argv[i] = 0;
    tmp->argv[argv_pipe(tmp)] = 0;
    tmp_and_new(tmp, new, str);
    put_redirection(new);
    remove_redi(new);
}

void    parsing_cmd(char *str, t_cmd **cur)
{
    int     k;
    t_cmd   *tmp;

    check_right(str);
    k = check_cmd_env(str);
    if (k > 0)
    {
        (*cur)->next = parsing_cmd_env(str);
        while (str[k] == ' ' | str[k] == '|')
            k++;
        str = str + k;
    }
    if (ft_strlen(str) == 0)
        return ;
    tmp = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
    init_cmd(str, tmp);
    tmp->argc = return_j(tmp, str);
    if (k <= 0)
        (*cur)->next = tmp;
    else
        (*cur)->next->next = tmp;
    if (k == -2)
        tmp->shell_var = 1;
    finish_cmd(tmp, str);
}
