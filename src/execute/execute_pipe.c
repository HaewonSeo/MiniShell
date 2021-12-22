/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 18:32:45 by haseo             #+#    #+#             */
/*   Updated: 2021/12/22 19:02:46 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void exec_pipe_fork(t_cmd *cmd)
{
	char	*cmd_path;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_perror("fork", 1);
	else if (pid == 0)
	{
		if (cmd->pipe)
		{
			if (dup2(cmd->next->fd[1], STDOUT_FILENO) == -1)
				ft_perror("dup2", 1); //stdout과 연결된 fd 2는 자동으로 닫히고, fd[1]을 복사하여 stdout에 연결한다.
			close(cmd->next->fd[1]);
		}
		else
		{
			if (dup2(cmd->fd[0], STDIN_FILENO) == -1)
				ft_perror("dup2", 1);	// fd[0]을 복사하여 STDIN에 연결함
			close(cmd->fd[0]);	// cmd 실행 후 fd[0] 닫기
		}
		exec_cmd_child(cmd);
	}
	waitpid(pid, NULL, 0);
}

/*
	exec_pipe 및 exec_pipe_fork 기능

	1. cmd에 pipe가 존재하는 경우
		1) next_cmd의 pipe_prev 변수를 1로 만들고 next cmd에서 pipe를 생성한다(pipe())
		2) 자식 프로세스를 생성하고 next_cmd의 fd[]와 STDOUT를 설정한다. (exec_pipe_fork())
		3) 현재 cmd를 실행한다.

	2. 직전 cmd에 pipe가 존재하는 경우
		1) 자식 프로세스를 생성하고 현재 cmd의 fd[]와 STDIN을 설정한다. (exec_pipe_fork())
		2) 현재 cmd를 실행한다

	- dup2()를 부모 프로세스에서 사용하면 안 되는 이유
		- 처음에는 dup2()를 사용해서 부모 프로세스에서 pipe를 설정하려 했으나 오류 발생
		- dup2()의 2번째 인자인 STD~ 가 닫히게 되면서, 자식 프로세스가 STD~ 를 사용하지 못하는데서 문제가 발생한 것 같다..
		-> 확실하지 않음
		-> 따라서, 자식 프로세스에서 dup2()를 호출하도록 함

	- 개념이 어려우니 이해하기 어려우면 질문 주세요!!

*/

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
		// if (dup2(cur->next->fd[1], STDOUT_FILENO) == -1)
		// 	ft_perror("dup2", 1); //stdout과 연결된 fd 2는 자동으로 닫히고, fd[1]을 복사하여 stdout에 연결한다.
		exec_pipe_fork(cur);	// 출력이 pipe로 전달됨
		close(cur->next->fd[1]);	// cmd 실행 후 fd[1] 닫기

	}
	// 파이프가 이미 생성된 경우
	else
	{
		// if (dup2(cur->fd[0], STDIN_FILENO) == -1)
		// 	ft_perror("dup2", 1);	// fd[0]을 복사하여 STDIN에 연결함
		exec_pipe_fork(cur);
		close(cur->fd[0]);	// cmd 실행 후 fd[0] 닫기
	}
}

/*

	pipe 개념 이해용

static void exec_pipe2(t_cmd *cur)
{
	pid_t	pid;
	int		fd[2];

	// cur->next->left_pipe = 1;
	pipe(fd);

	pid = fork();
	if (pid == 0)	// child : cur이 먼저 실행됨
	{
#ifdef TEST
		printf("Child : %s\n", cur->argv[0]);
#endif
		close(fd[0]);	// 사용하지 않는 read 닫기
		dup2(fd[1], STDOUT_FILENO); //stdout과 연결된 fd 2는 자동으로 닫히고, fd[1]을 복사하여 stdout에 연결한다.
		exec_cmd(cur);	// 출력이 pipe로 전달됨
		close(fd[1]);	// cmd 실행 후 fd[1] 닫기
	}
	// parent : cur->next 실행됨, cur의 결과를 입력으로 받는다.
	waitpid(pid, NULL, 0); // 자식이 종료될 때까지 대기
#ifdef TEST
		printf("Parent : %s\n", cur->next->argv[0]);
#endif

	close(fd[1]);	// 사용하지 않는 write 닫기
	dup2(fd[0], STDIN_FILENO);	// STDIN에 fd[0]이 연결됨
	exec_cmd(cur->next);
	close(fd[0]);	// cmd 실행 후 fd[0] 닫기
}
*/
