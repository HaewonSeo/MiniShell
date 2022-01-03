/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 22:21:41 by haseo             #+#    #+#             */
/*   Updated: 2022/01/03 22:21:54 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin_on_child(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "env"))
		return (1);
	return (0);
}

static int	is_builtin_on_parent(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

void	exec_builtin(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->argv[0], "cd"))
		ft_cd(cmd);
	else if (!ft_strcmp(cmd->argv[0], "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd->argv[0], "env"))
		ft_env(cmd);
	else if (!ft_strcmp(cmd->argv[0], "export"))
		ft_export(cmd);
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		ft_unset(cmd);
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		ft_exit();
}
