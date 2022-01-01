
#include "minishell.h"

char    *re_make_str(char *str)
{
    int     i;
    int     j;
    char    *new;

    i = 0;
    while(str[i] && str[i] == ' ')
        i++;
    j = i;
    while (str[i] && str[i] != ' ')
        i++;
    new = ft_substr(str, j, i - j);
    return (new);
}

int check_cmd_env(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] == ' ')
        i++;
    while (str[i] && str[i] != ' ')
    {
        if (str[i] == '<' || str[i] == '>' || str[i] == '|')
            return (-1);
        if (str[i] == '=' && i != 0)
        {
            while (str[i] && str[i] != ' ')
                i++;
            return (i);
        }
        i++;
    }
    return (0);
}

t_cmd   *parsing_cmd_env(char *str)
{
    t_cmd   *new;

    str = re_make_str(str);
    new = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
    new->argc = 1;
    new->argv = (char **)malloc(sizeof(char *) * 1);
    new->redirection = 0;
    new->pipe = 0;
    new->quote = 0;
    new->fd[0] = 0;
    new->fd[1] = 0;
    new->pipe_prev = 0;
    new->shell_var = 1;
    new->redir = (t_redir *)ft_calloc(1, sizeof(t_redir));
    new->next = NULL;
    new->argv[0] = ft_substr(str, 0, ft_strlen(str));//
    return (new);
}
