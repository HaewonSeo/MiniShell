/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 18:36:01 by haseo             #+#    #+#             */
/*   Updated: 2022/01/04 11:10:39 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(void)
{
	printf("exit\n");
	free_envp(g_info.envp);
	free_shell(g_info.shell);
	free_cmd(g_info.head_cmd);
// #ifdef WSL
// 	set_canonical_mode();
// #endif
	exit(0);
}
