/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 18:34:19 by haseo             #+#    #+#             */
/*   Updated: 2022/01/03 22:23:14 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_path(char *cmd)
{
	char		**paths;
	char		*_cmd;
	char		*cmd_path;
	int			i;
	struct stat	st;

	if (stat(cmd, &st) == 0)
		return (cmd);
	paths = ft_split(get_env(g_info.envp, "PATH"), ':');
	_cmd = ft_strdup("/");
	_cmd = ft_strjoin(_cmd, cmd);
	i = -1;
	while (paths[++i])
	{
		cmd_path = ft_strdup(paths[i]);
		cmd_path = ft_strjoin(cmd_path, _cmd);
		if (stat(cmd_path, &st) == 0)
			break ;
		free(cmd_path);
		cmd_path = NULL;
	}
	ft_free2d(paths);
	free(_cmd);
	return (cmd_path);
}

void	exec_cmd_child(t_cmd *cmd)
{
	char	*cmd_path;

	if (is_builtin_on_child(cmd->argv[0]))
		exec_builtin(cmd);
	else
	{
		cmd_path = get_cmd_path(cmd->argv[0]);
		if (!cmd_path)
			ft_perror3(cmd->argv[0], "command not found", 127);
		else
		{
			if (execve(cmd_path, cmd->argv, g_info.envp) == -1)
				ft_perror("execve", 1);
			free(cmd_path);
		}
	}
}

static void	exec_cmd_fork(t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		ft_perror("fork", 1);
	else if (pid == 0)
	{
		if (cmd->redirection)
			set_redirection(cmd);
		exec_cmd_child(cmd);
		exit(g_info.exit_status);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_info.exit_status = WEXITSTATUS(status);
		else
			g_info.exit_status = 1;
	}
}

void	exec_cmd(t_cmd *cmd)
{
	if (cmd->shell_var)
		add_shell(g_info.shell, cmd->argv[0]);
	else if (is_builtin_on_parent(cmd->argv[0]))
		exec_builtin(cmd);
	else
		exec_cmd_fork(cmd);
}
