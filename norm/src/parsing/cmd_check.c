/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 21:17:59 by hyejung           #+#    #+#             */
/*   Updated: 2022/01/03 23:46:03 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_cmd(t_cmd *tmp)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (tmp->argv[j])
		j++;
	while (i < j)
	{
		if (is_builtin(tmp->argv[i]))
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

int	check_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			return (1);
		else if (str[i] == '\"')
			return (2);
		i++;
	}
	return (0);
}

int	where_redi(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>')
		{
			if (str[i + 1] == '>')
				return (i + 2);
			else if (str[i + 1] == ' ')
				return (i + 1);
		}
		else if (str[i] == '<')
		{
			if (str[i + 1] == '<')
				return (i + 2);
			else if (str[i + 1] == ' ')
				return (i + 1);
		}
		i++;
	}
	return (-1);
}

int	where_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			return (i + 1);
		i++;
	}
	return (-1);
}

int	where_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			return (i);
		if (str[i] == '\"')
			return (i);
		i++;
	}
	return (-1);
}
