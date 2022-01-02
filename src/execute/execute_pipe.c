/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 18:32:45 by haseo             #+#    #+#             */
/*   Updated: 2022/01/02 20:41:33 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void set_pipe(t_cmd *cmd)
{
	if (cmd->redirection)
			set_redirection(cmd);
	if (cmd->pipe)
	{
		if (dup2(cmd->next->fd[1], STDOUT_FILENO) == -1)
			ft_perror("dup2", 1);
		close(cmd->next->fd[1]);
	}
	if (cmd->pipe_prev)
	{
		if (dup2(cmd->fd[0], STDIN_FILENO) == -1)
			ft_perror("dup2", 1);
		close(cmd->fd[0]);
	}
}

static void exec_pipe_fork(t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		ft_perror("fork", 1);
	else if (pid == 0)
	{
		set_pipe(cmd);
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

void exec_pipe(t_cmd *cur)
{
#ifdef TEST11
		printf("cmd : %s\n", cur->argv[0]);
		printf("fd[0] : %d fd[1] : %d \n", cur->fd[0], cur->fd[1]);
#endif
	if (cur->pipe)
	{
		cur->next->pipe_prev = 1;
		pipe(cur->next->fd);
	}
	exec_pipe_fork(cur);
	if (cur->pipe)
		close(cur->next->fd[1]);
	if (cur->pipe_prev)
		close(cur->fd[0]);
}
