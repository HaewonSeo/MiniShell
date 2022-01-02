/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 22:24:47 by haseo             #+#    #+#             */
/*   Updated: 2022/01/01 22:30:14 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	set_redirection() 기능

	cmd 수정 필요
		- redirection 기호를 기준으로 cmd를 분리하는 방식에서
		- redirection 기호 다음 arg는 따로 저장하는 방식으로 수정 필요

	redirection 이 존재하는 경우 실행 흐름
		1. redirection 기호가 있다면, cmd를 파싱해서 filename을 저장..
			- redirection 관련 정보들은 argv 에 저장되지 않는다!
				-> argv, argc 수정 필요
			- (ex) $ sort < words1.txt > words2.txt >> words3.txt
				redir->l : words1.txt
				redir->ll : NULL
				redir->r : words2.txt
				redir->rr : words3.txt

		2. 파싱한 정보를 통해 File Description을 설정

		3. 명령어 실행


	즉, redirection이 존재하는 경우 File Description을 설정해야 하고
	이를 set_redirection()에서 설정한다.

	고민1 : redirction에 대한 setting을 어떤 프로세스에서 실행할지
		1) 부모 프로세스에서 set한 이후에 fork하고 자식 프로세스를 실행시킬 것인지
		2) 자식 프로세스에서 set한 이후에 자식 프로세스를 실행할 것인지

		--> 2) 자식 프로세스에서 set해야 함.
		왜냐하면, 자식 프로세스가 생성되면 fd 0, 1, 2가 초기화되기 때문


	고민2 : arg에 대한 수정을 어느 단계에서 진행할지
		1) 파싱에서 먼저 진행
		2) 명령어 실행 단계에서 진행

		--> 1) 파싱 단계에서 진행
*/

static void	set_l(char *fname)
{
	int	fd;

	fd = open(fname, O_RDONLY);
	if (fd < 0)
		ft_perror1(fname, "No such file or directory", (int)EPERM);
		// exit(EPERM);
	else
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			ft_perror("dup2", 1);
		close(fd);
	}
}

/*
	set_ll() 기능

	ex1) $ sort << EOF
		STDIN으로 받은 입력을 임시 파일에 저장하고
		이 파일이 sort 명령어를 실행하기 위한 입력으로 적용된다.
		<< 우측의 문자열이 delimiter가 되고 delimeter가 입력되면 임시 파일에 입력이 중단된다.

	ex2) $ sort << EOF > output.txt
		입력은 위 예제와 동일하게 받게 되고
		sort의 실행 결과가 output.txt 에 저장된다.

	ex3) $ cat << EOF1
		> h
		> a
		> EOF1
		h
		a

	동작 순서
		1. 임시 파일을 creat
		2. STDIN으로 받는 값을 임시파일에 저장
		3. Delimiter가 입력되면 중단
		4. STDIN을 임시 파일의 fd에 연결
*/

static void	set_ll(char *delimiter)
{
	int	fd;
	char *input;

	fd = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0744); // __O_TMPFILE 을 사용하면 임시 파일을 만들 수 있지만, 허용되지 않는 함수가 필요하다.
	if (fd < 0)
		ft_perror1("tmp", "No such file or directory", (int)EPERM);
	else
	{
		while (1)
		{
			ft_putstr_fd("> ", STDOUT_FILENO);
			input = prompt4();
			if (!strcmp(input, delimiter))
			{
				free(input);
				break;
			}
			ft_putstr_fd(input, fd);
			ft_putstr_fd("\n", fd);
			ft_putstr_fd("\n", STDOUT_FILENO);
			free(input);
		}
		close(fd);
		ft_putstr_fd("\n", STDOUT_FILENO);
		set_l("tmp");	// lseek()를 사용할 수 없으므로, 새로 fd를 open해서 STDIN에 연결
		// tmp.txt 파일 삭제 생략됨
	}
}

static void	set_r(char *fname)
{
	int	fd;

	fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		ft_perror1(fname, "No such file or directory", (int)EPERM);
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			ft_perror("dup2", 1);
		close(fd);
	}
}

static	void	set_rr(char *fname)
{
	int	fd;

	fd = open(fname, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		ft_perror1(fname, "No such file or directory", (int)EPERM);
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			ft_perror("dup2", 1);
		close(fd);
	}
}

void	set_redirection(t_cmd *cur)
{
	if (cur->redir->l)
		set_l(cur->redir->l);
	if (cur->redir->ll)
		set_ll(cur->redir->ll);
	if (cur->redir->r)
		set_r(cur->redir->r);
	if (cur->redir->rr)
		set_rr(cur->redir->rr);
}
