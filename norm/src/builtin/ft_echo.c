/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:04:50 by haseo             #+#    #+#             */
/*   Updated: 2022/01/07 18:35:54 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_val(char *arg)
{
	int	j;

	if (ft_strchr(arg, '$'))
	{
		j = 0;
		while (arg[j] && arg[j] != '$')
		{
			printf("%c", arg[j]);
			j++;
		}
		echo_env(ft_strchr(arg, '$'));
	}
	else
		printf("%s", arg);
}

void	echo_env(char *arg)
{
	char	*key;
	char	*value;

	if (arg[1] == '?')
	{
		printf("%d", g_info.exit_status);
		echo_val(&arg[2]);
	}
	else
	{
		key = &arg[1];
		value = get_env(g_info.envp, key);
		if (value)
		{
			printf("%s", value);
			return ;
		}
		value = get_shell(&g_info, key);
		if (value)
			printf("%s", value);
	}
}

void	ft_echo(t_cmd *cmd)
{
	bool	opt_n;
	int		i;

	opt_n = false;
	i = 0;
	if (!strcmp(cmd->argv[1], "-n"))
		opt_n = true;
	if (opt_n == true)
		++i;
	while (++i < cmd->argc)
	{
		if (cmd->quote == 1)
			printf("%s", cmd->argv[i]);
		else if (!ft_strcmp(cmd->argv[i], "$"))
			printf("%s", cmd->argv[i]);
		else if (ft_strchr(cmd->argv[i], '$'))
			echo_val(cmd->argv[i]);
		else
			printf("%s", cmd->argv[i]);
		if (i < cmd->argc - 1)
			printf(" ");
	}
	if (!opt_n)
		printf("\n");
	g_info.exit_status = 0;
}
