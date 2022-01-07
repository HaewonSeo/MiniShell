/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 20:53:43 by hyejung           #+#    #+#             */
/*   Updated: 2022/01/07 18:00:26 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	argv_pipe(t_cmd *tmp)
{
	int	i;

	i = 0;
	while (tmp->argc > 0 && tmp->argv[i])
	{
		if (tmp->argv[i][0] == '|')
			break ;
		i++;
	}
	return (i);
}

void	tmp_and_new(t_cmd *tmp, t_cmd *new, char *str)
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

int	check_quote_double(char *str)
{
	int		i;
	char	c;
	char	d;

	i = -1;
	c = 0;
	d = 0;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			c = str[i];
		if (c != 0)
			break ;
	}
	i = ft_strlen(str);
	while (str[--i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			d = str[i];
		if (d != 0)
			break ;
	}
	if (c == d && c != 0)
		return (1);
	return (0);
}

int	check_right(char *str)
{
	int	i;

	i = ch_right_quote(str);
	if (i == 0 && check_quote_double(str) == 0)
		i = ch_right_pipe(str);
	if (i == 0 && check_quote_double(str) == 0)
		i = ch_right_redi(str);
	return (i);
}

void	put_redirection(t_cmd *tmp)
{
	int	i;

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
		}
		else if (tmp->argv[i][0] == '>')
		{
			if (!tmp->argv[i][1])
				tmp->redir->r = tmp->argv[i + 1];
			else if (tmp->argv[i][1] == '>')
				tmp->redir->rr = tmp->argv[i + 1];
		}
		i++;
	}
}
