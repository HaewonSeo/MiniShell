/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:04:50 by haseo             #+#    #+#             */
/*   Updated: 2022/01/03 22:00:47 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echo_env(char *arg)
{
	char	*key;
	char	*value;

	if (arg[1] == '?')
		printf("%d", g_info.exit_status);
	else
	{
		key = &arg[1];
		value = get_env(g_info.envp, key);
		if (value)
		{
			printf("%s ", value);
			return ;
		}
		value = get_shell(&g_info, key);
		if (value)
			printf("%s ", value);
	}
}

void	ft_echo(t_cmd *cmd)
{
	bool	opt_n;
	int		i;

	opt_n = false;
	i = 0;
	if (!strcmp(cmd->argv[1], "-n"))
	{
		opt_n = true;
		++i;
	}
	while (++i < cmd->argc)
	{
		if (cmd->quote == 1)
			printf("%s ", cmd->argv[i]);
		else if (cmd->argv[i][0] == '$')
			echo_env(cmd->argv[i]);
		else
			printf("%s ", cmd->argv[i]);
	}
	if (!opt_n)
		printf("\n");
	g_info.exit_status = 0;
}
