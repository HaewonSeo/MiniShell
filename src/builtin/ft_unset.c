/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 18:44:18 by haseo             #+#    #+#             */
/*   Updated: 2022/01/02 17:25:50 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_unset(t_cmd *cmd)
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
			del_envp(&g_info, cmd->argv[i]);
			// del_shell(&g_info, cmd->argv[i]); (에러) 동작안하고 무한루프 빠짐
#ifdef TEST
			printf("[shell list]\n");		// (에러) 쉘 변수 리스트에 환경변수 SHELL이 존재함
			print_shell(g_info.shell);		// SHELL=/bin/bash 첫항에 존재
#endif
		}
	}
}
