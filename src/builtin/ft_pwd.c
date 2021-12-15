/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:14:21 by haseo             #+#    #+#             */
/*   Updated: 2021/12/15 19:03:03 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	pwd 기능

	현재 작업 디렉토리를 출력
		- getcwd를 이용할 수도 있고 - 이 방식으로 구현함
		- 환경변수 $PATH를 출력해도 됨
*/

void ft_pwd()
{
	printf("%s\n", getcwd(NULL, 0));
	g_info.exit_status = 0;
}

/*
	추가로 fork() & execve() 를 이용하여 /bin 디렉토리에 존재하는 bin 파일을 실행하는 방법도 존재
	-> 그러나 /bin 디렉토리에 존재하지 않는 command도 있기 때문에 적절치 않음
	-> 참고 용도

void ft_pwd(t_cmd *cmd)
{
	pid_t	pid;
	char	*cmd_path = "/bin/pwd";

	pid = fork();
	if (pid < 0)
		ft_perror("fork");
	else if (pid == 0)
	{
		// test version
		if (execve(cmd_path, g_info.argv, g_info.envp) == -1)
			ft_perror("execve");
		// cmd version
		// if (execve(cmd_path, cmd->argv, g_info.envp) == -1)
			// ft_perror("execve");
	}
	waitpid(pid, NULL, 0);
	g_info.exit_status = 0;
}

*/
