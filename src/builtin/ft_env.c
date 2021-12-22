/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:15:29 by haseo             #+#    #+#             */
/*   Updated: 2021/12/21 17:07:30 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	env 기능

	1. argumert와 옵션이 없는 경우 모든 환경변수를 출력

	2. argument가 있는 경우 argument로 주어진 명령을 실행

	3. argument가 key=value 형식인 경우, 환경변수를 추가한 이후 1번 동작 수행
		ex) $ env ABC=123
		- 아직 구현 안 한 상태
*/

void ft_env(t_cmd *cmd)
{
	int		i;
	pid_t	pid;

	if (cmd->argc == 1)
		print_envp(g_info.envp);
	else
	{
		pid = fork();
		if (pid < 0)
			ft_perror("fork", (int)EPERM);
		else if (pid == 0)
		{
			if (execve(cmd->argv[1], &cmd->argv[1], g_info.envp) == -1)
				ft_perror("execve", (int)EPERM);
		}
		waitpid(pid, NULL, 0);
		g_info.exit_status = 0;
	}
}
