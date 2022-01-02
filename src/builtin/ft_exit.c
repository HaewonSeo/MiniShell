/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 18:36:01 by haseo             #+#    #+#             */
/*   Updated: 2022/01/02 17:52:24 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exit_with_set_mode(int errnum)
{
#ifdef WSL
	set_canonical_mode();
#endif
	g_info.exit_status = 0;
	exit(errnum);
}

void	ft_exit()
{
	printf("exit\n");
	free_envp(g_info.envp);
	free_cmd(g_info.head_cmd);
	ft_exit_with_set_mode(0);
}
