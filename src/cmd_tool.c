
#include "minishell.h"

int   check_i(char *str, t_cmd *tmp, int i, int j, int mid)
{
    char    c;

    c = str[i];
    i++;
    while (str[i] && str[i] != c)
        i++;
    tmp->argv[j] = ft_substr(str, mid + 1, i - mid - 1);
    i++;
    return (i);
}

int argv_pipe(t_cmd *tmp)
{
    int i;

    i = 0;
    while (tmp->argv[i])
    {
        if (tmp->argv[i][0] == '|')
            break ;
        i++;
    }
    return (i);
}

void    tmp_and_new(t_cmd *tmp, t_cmd *new, char *str)
{
    new->shell_var = 0;
    new->pipe_prev = 1;
    new->pipe = check_pipe(new);
    new->redirection = check_redi(str + where_pipe(str));
    tmp->next = new;
    new->next = NULL;
    if (where_quote(str) > where_pipe(str))
        tmp->quote = 0;
    if (new->pipe > 0)
        re_parsing_cmd(new, str + where_pipe(str));
    return ;
}

int return_j(t_cmd *tmp, char *str)
{
    int i;
    int j;
    int mid;

    i = 0;
    j = 0;
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
    tmp->pipe = check_pipe(tmp);
    tmp->redirection = check_redi(str);
    return (j);
}

void    check_right(char *str) // | < << > >> " '
{
    ch_right_quote(str);
    ch_right_pipe(str);
    ch_right_redi(str);
}
