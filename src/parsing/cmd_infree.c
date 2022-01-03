/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_infree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejung <hyejung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 21:18:08 by hyejung           #+#    #+#             */
/*   Updated: 2022/01/03 21:18:10 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    tmp->redir = (t_redir *)ft_calloc(1, sizeof(t_redir));
}

void    free_cmd(t_cmd *tmp)
{
    t_cmd   *del;
    int     i;

    while (tmp)
    {
        del = tmp;
        tmp = tmp->next;
        i = 0;
        while (i++ < del->argc)
            free(del->argv[i]);
        if (del->redirection == 1)
            free(del->redir->l);
        if (del->redirection == 2)
            free(del->redir->ll);
        if (del->redirection == 3)
            free(del->redir->r);
        if (del->redirection == 4)
            free(del->redir->rr);
        free(del->redir);
        free(del->argv);
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
        tmp->argv[j++] = ft_substr(str, mid, i - mid);
        i++;
    }
    tmp->argv[j] = 0;
    if (tmp->quote != 0)
        j = parsing_cmd_qu(str, tmp);
    tmp->pipe = check_pipe(tmp);
    tmp->redirection = check_redi(tmp);
    return (j);
}

void    finish_cmd(t_cmd *tmp, char *str)
{
    if (tmp->pipe == 1 && where_pipe(str) < where_redi(str))
        tmp->redirection = 0;
    if (where_quote(str) > where_pipe(str) && where_pipe(str) != -1)
        tmp->quote = 0;
    if (tmp->pipe > 0)
        re_parsing_cmd(tmp, str + where_pipe(str));
    put_redirection(tmp);
    remove_redi(tmp);
}
