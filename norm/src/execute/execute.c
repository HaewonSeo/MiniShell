/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 18:10:49 by haseo             #+#    #+#             */
/*   Updated: 2022/01/07 17:56:19 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_input(t_cmd *cmd)
{
	t_cmd	*cur;

	if (cmd->quote < 0)
		return ;
	cur = cmd;
	while (cur)
	{
		if (cur->pipe || cur->pipe_prev)
			exec_pipe(cur);
		else
			exec_cmd(cur);
		cur = cur->next;
	}
}
