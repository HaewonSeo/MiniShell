/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 18:10:49 by haseo             #+#    #+#             */
/*   Updated: 2021/12/15 18:56:11 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo")
	|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "env")
	|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "export")
	|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "exit"))
		return (true);
	return (false);
}

static void exec_builtin(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->argv[0], "cd"))
		ft_cd(cmd);
	else if (!ft_strcmp(cmd->argv[0], "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd->argv[0], "env"))
		ft_env();
	else if (!ft_strcmp(cmd->argv[0], "export"))
		ft_export(cmd);
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		ft_unset(cmd);
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		ft_exit(cmd);
	else
		return (0);
}

void exec_cmd()
{
	t_cmd *cur;

	cur = head_cmd;
	// cmd list를 실행
	while (cur->next)
	{
		cur = cur->next;
		if (cur->argv[0])
		{
			if (is_builtin(cur->argv[0]))
				exec_builtin(cur);
			else if (cur->redirection)
				exec_redirection(cur);
			else if (cur->pipe)
				exec_pipe(cur);
		}
	}
	// free cmd list
}
