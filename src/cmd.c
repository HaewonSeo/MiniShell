
#include "minishell.h"

int check_cmd(t_cmd *tmp)
{
    int i;
    int j;
    int k;

    i = 0;
    j = 0;
    k = 0;
    while (tmp->argv[j])
        j++;
    while (i < j)
    {
        if (!ft_strcmp(tmp->argv[i], "cd") || !ft_strcmp(tmp->argv[i], "echo")
	    || !ft_strcmp(tmp->argv[i], "pwd") || !ft_strcmp(tmp->argv[i], "env")
	    || !ft_strcmp(tmp->argv[i], "export") || !ft_strcmp(tmp->argv[i], "export")
	    || !ft_strcmp(tmp->argv[i], "unset") || !ft_strcmp(tmp->argv[i], "exit"))
            k++;
        if (tmp->pipe == 0)
            break ;
        else
        {
            while (ft_strcmp(tmp->argv[i], "-"))
                i++;
        }
    }
	return (k);
}

void    parsing_cmd(char *str, t_cmd **cur)
{
    int     i;
    int     j;
    int     mid;
    t_cmd   *tmp;

    i = 0;
    j = 0;
    tmp = init_cmd(str);
    while(i < ft_strlen(str))
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
	tmp->argv[j] = NULL;
    tmp->argc = j;
    tmp->pipe = check_pipe(tmp);
    tmp->redirection = check_redi(tmp);

    /*
    double free 발생! -> 수정 필요

    if (check_cmd(tmp) - tmp->pipe != 1)
        free_cmd(tmp);
    */

    (*cur)->next = tmp;
    return ;
}
