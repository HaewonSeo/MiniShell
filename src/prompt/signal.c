/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 14:26:24 by haseo             #+#    #+#             */
/*   Updated: 2022/01/02 21:04:17 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("SIGINT : print a new prompt on a newline.\n");
		g_info.signal = 1;
		g_info.exit_status = 130;
	}
	else if (signum == SIGQUIT)
	{
		printf("SIGQUIT : DO NOTHING.\n");
		// return ;
	}
}
