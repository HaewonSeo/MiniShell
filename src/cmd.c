
#include "minishell.h"

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



void    re_parsing_cmd(t_cmd *tmp, char *str)
{
    int     i;
    int     j;
    int     k;
    t_cmd   *new;

    i = 0;
    j = 0;
    new = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
    new->quote = check_quote(str);
    while (tmp->argv[i])
    {
        if (tmp->argv[i][0] == '|')
            break ;
        else if (tmp->argv[i][0] == '>')
        {
            if (tmp->argv[i][1] == '>' || !tmp->argv[i][1])
                break ;
        }
        else if (tmp->argv[i][0] == '<')
        {
            if (tmp->argv[i][1] == '<' || !tmp->argv[i][1])
                break ;
        }
        i++;
    }
    k = i + 1;
    new->argv = (char **)malloc(sizeof(char *) * (tmp->argc - k));
    new->argc = tmp->argc - k;
    tmp->argc = tmp->argc - new->argc - 1;
    while (tmp->argv[k])
        new->argv[j++] = tmp->argv[k++];
    new->argv[j] = 0;
    tmp->argv[i] = 0;
    new->pipe = check_pipe(new);
    new->redirection = check_redi(new);
    tmp->next = new;
    new->next = NULL;
    if (where_quote(str) > where_pire(str))
        tmp->quote = 0;
    if (new->pipe > 0 || new->redirection > 0)
        re_parsing_cmd(new, str + where_pire(str));
}

void    parsing_cmd(char *str, t_cmd **cur)
{
    int     i;
    int     j;
    int     mid;
    t_cmd   *tmp;

    i = 0;
    j = 0;
    tmp = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
    init_cmd(str, tmp);
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
    tmp->redirection = check_redi(tmp);
    (*cur)->next = tmp;
    if (where_quote(str) > where_pire(str))
        tmp->quote = 0;
    if (tmp->pipe > 0 || tmp->redirection > 0)
        re_parsing_cmd(tmp, str);
    return ;
}
