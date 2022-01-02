/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:15:29 by haseo             #+#    #+#             */
/*   Updated: 2022/01/02 17:23:17 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_cmd *cmd)
{
	t_cmd	*new_cmd;

	if (cmd->argc == 1)
		print_envp(g_info.envp);
	else
	{
		new_cmd = cmd;
		new_cmd->argv = &(new_cmd->argv[1]);
		(new_cmd->argc)--;
		if (ft_strchr(new_cmd->argv[0], '='))
		{
			new_cmd->shell_var = 1;
			print_envp(g_info.envp);
			printf("%s\n", new_cmd->argv[0]);
		}
		exec_cmd(new_cmd);
	}
}
