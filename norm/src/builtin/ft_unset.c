/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 18:44:18 by haseo             #+#    #+#             */
/*   Updated: 2022/01/04 17:30:05 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_cmd *cmd)
{
	int		i;

	g_info.exit_status = 0;
	i = 0;
	while (++i < cmd->argc)
	{
		if (!ft_strcmp(cmd->argv[i], "$"))
			ft_perror2("unset", "`$'", "not a valid identifier", 1);
		else
		{
			del_env2(g_info.envp, cmd->argv[i]);
			del_shell(&g_info, cmd->argv[i]);
		}
	}
}
