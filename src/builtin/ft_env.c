/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:15:29 by haseo             #+#    #+#             */
/*   Updated: 2021/12/15 19:03:23 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	env 기능

	1. argumert와 옵션이 없는 경우 모든 환경변수를 출력

	2. argument가 있는 경우 argument로 주어진 명령을 실행
*/

void ft_env(t_cmd *cmd)
{
	int		i;
	pid_t	pid;

	if (!cmd->arg[1])
		print_env();
	else
	{
		pid = fork();
		if (pid < 0)
			ft_perror("fork");
		else if (pid == 0)
		{
			if (execve(cmd->argv[1], &cmd->argv[1], g_info.envp) == -1)
				ft_perror("execve");
		}
		waitpid(pid, NULL, 0);
		g_info.exit_status = 0;
	}
}
