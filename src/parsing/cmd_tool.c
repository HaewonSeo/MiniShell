
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
    tmp->next = new;
    new->next = NULL;
    if (where_quote(str) > where_pipe(str))
        tmp->quote = 0;
    if (new->pipe > 0)
        re_parsing_cmd(new, str + where_pipe(str));
    new->redirection = check_redi(new);
    return ;
}

void    check_right(char *str)
{
    ch_right_quote(str);
    ch_right_pipe(str);
    ch_right_redi(str);
}

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
