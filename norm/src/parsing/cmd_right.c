/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_right.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 21:18:17 by hyejung           #+#    #+#             */
/*   Updated: 2022/01/07 18:04:56 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	printf_error(int i)
{
	if (i == 1)
		ft_perror("unexpected EOF while looking for matching 'quote'", 258);
	else if (i == 2)
		ft_perror("syntax error near unexpected token 'newline'", 258);
	else if (i == 3)
		ft_perror("syntax error near unexpected token '|'", 258);
	else if (i == 4)
		ft_perror("syntax error near unexpected token `redirection'", 258);
	else if (i == 5)
		ft_perror("syntax error: unexpected end of file", 258);
	if (i == 1)
		return (-1);
	else
		return (-2);
}

int	ch_right_redi_2(char *str, int i)
{
	int	j;

	j = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (i == (int)ft_strlen(str))
		j = printf_error(2);
	else
	{
		while (i < (int)ft_strlen(str) && str[i] == ' ')
		{
			i++;
			if (str[i] == '|')
				j = printf_error(3);
			if (str[i] == '>' || str[i] == '<')
				j = printf_error(4);
		}
	}
	return (j);
}

int	ch_right_redi(char *str)
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
			return (ch_right_redi_2(str, i));
		}
		else if (str[i] == '<')
		{
			i++;
			if (str[i] == '<')
				i++;
			return (ch_right_redi_2(str, i));
		}
		i++;
	}
	return (0);
}

int	ch_right_pipe(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			i++;
			while (str[i] && str[i] == ' ')
				i++;
			if (str[i] == '|')
				j = printf_error(3);
			if (str[i] == '>' || str[i] == '<')
				j = printf_error(2);
			if (!str[i])
				j = printf_error(5);
		}
		i++;
	}
	return (j);
}

int	ch_right_quote(char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (i >= (int)ft_strlen(str))
				j = printf_error(1);
		}
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			if (i >= (int)ft_strlen(str))
				j = printf_error(1);
		}
	}
	return (j);
}
