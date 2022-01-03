/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_right.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 21:18:17 by hyejung           #+#    #+#             */
/*   Updated: 2022/01/04 01:32:09 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printf_error(int i)
{
	if (i == 1)
	{
		ft_perror("unexpected EOF while looking for matching 'quote'", 2);
		// printf("error : quote error\n");
		// return ;
	}
	else if (i == 2)
	{
		ft_perror("syntax error near unexpected token 'newline'", 2);
		// printf("error : parse error near `|'\n");
		// return ;
	}
	else if (i == 3)
	{
		ft_perror("syntax error near unexpected token '|'", 2);
		// printf("error : parse error near `\\n'\n");
		// return ;
	}
}

void	ch_right_redi_2(char *str, int i)
{
	while (str[i] && str[i] == ' ')
	{
		i++;
		if (str[i] == '|')
			printf_error(3);
		if (str[i] == '>' || str[i] == '<')
			printf_error(3);
		if (!str[i])
			printf_error(3);
	}
}

void	ch_right_redi(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>')
		{
			i++;
			if (str[i] == '>')
				i++;
			ch_right_redi_2(str, i);
		}
		if (str[i] == '<')
		{
			i++;
			if (str[i] == '<')
				i++;
			ch_right_redi_2(str, i);
		}
		i++;
	}
}

void	ch_right_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			i++;
			while (str[i] && str[i] == ' ')
				i++;
			if (str[i] == '|')
				printf_error(2);
			if (str[i] == '>' || str[i] == '<')
				printf_error(2);
			if (!str[i])
				printf_error(2);
		}
		i++;
	}
}

void	ch_right_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (i >= (int)ft_strlen(str))
				printf_error(1);
		}
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			if (i >= (int)ft_strlen(str))
				printf_error(1);
		}
		i++;
	}
}
