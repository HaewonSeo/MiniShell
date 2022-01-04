/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pire.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 21:17:37 by hyejung           #+#    #+#             */
/*   Updated: 2022/01/04 17:58:59 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe(t_cmd *tmp)
{
	int	i;

	i = 0;
	while (tmp->argv[i])
	{
		if (tmp->argv[i][0] == '|')
		{
			if (ft_strlen(tmp->argv[i]) == 1)
				return (1);
			else
				i++;
		}
		else
			i++;
	}
	return (0);
}

int	check_redi(t_cmd *tmp)
{
	int	i;

	i = 0;
	while (tmp->argv[i])
	{
		if (tmp->argv[i][0] == '<')
		{
			if (ft_strlen(tmp->argv[i]) == 1)
				return (1);
			else if (tmp->argv[i][1] == '<' && ft_strlen(tmp->argv[i]) == 2)
				return (2);
		}
		else if (tmp->argv[i][0] == '>')
		{
			if (ft_strlen(tmp->argv[i]) == 1)
				return (3);
			else if (tmp->argv[i][1] == '>' && ft_strlen(tmp->argv[i]) == 2)
				return (4);
		}
		i++;
	}
	return (0);
}

void	free_argv(char **tmp, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
}

void	re_parsing_cmd_env(t_cmd *tmp)
{
	int	i;

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
