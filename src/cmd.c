
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
    char    **str;

    i = 0;
    j = 0;
    str = (char **)malloc(sizeof(char *) * (tmp->argc - 2));
    while (tmp->argv[i])
    {
        if (tmp->argv[i][0] == '>' | tmp->argv[i][0] == '<')
            i = i + 2;
        str[j] = ft_substr(tmp->argv[i], 0, ft_strlen(tmp->argv[i]));
        i++;
        j++;
    }
    str[j] = 0;
    free_argv(tmp->argv, tmp->argc);
    tmp->argv = (char **)malloc(sizeof(char *) * j);
    i = 0;
    while (str[i])
    {
        tmp->argv[i] = ft_substr(str[i], 0, ft_strlen(str[i]));
        i++;
    }
    tmp->argv[i] = 0;
    tmp->argc = i;
    free_argv(str, i);
}

void    re_malloc_cmd(t_cmd *tmp, int len)
{
    int i;
    char    **str;

    i = 0;
    str = (char **)malloc(sizeof(char *) * len);
    while (i < len)
    {
        str[i] = ft_substr(tmp->argv[i], 0, ft_strlen(tmp->argv[i]));
        i++;
    }
    str[i] = 0;
    free_argv(tmp->argv, tmp->argc);
    tmp->argc = i;
    i = 0;
    while (i < tmp->argc)
    {
        tmp->argv[i] = ft_substr(str[i], 0, ft_strlen(str[i]));
        i++;
    }
    tmp->argv[i] = 0;
    free_argv(str, i);
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
    while (tmp->argv[k])
        new->argv[i++] = tmp->argv[k++];
    new->argv[i] = 0;
    re_malloc_cmd(tmp, i);
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
        (*cur)->next->next = tmp;//
    if (k == -2)
        tmp->shell_var = 1;
    finish_cmd(tmp, str);
}
