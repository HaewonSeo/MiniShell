/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 00:28:18 by haseo             #+#    #+#             */
/*   Updated: 2021/12/15 18:58:49 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exit_with_set_mode(int errno)
{
	// 프로그래밍이 종료되기 때문에, 동적 할당한 메모리 해제하는 기능을 추가해야 함
	set_canonical_mode();
	exit(errno);
}

// error msg 출력 & exit status 저장 & exit
void ft_perror(const char *str, int errno)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_info.exit_status = errno;
	// exit(errno);
}

/*
bash 의 error msg 출력 방식

(1)
shw2662@DESKTOP-F8LA849:~$ cd d d
bash: cd: too many arguments

(2)
shw2662@DESKTOP-F8LA849:~$ cd ~23
bash: cd: ~23: No such file or directory

- printf()를 사용하여 출력하는 방법
- stderr 스트림으로 출력하는 방법
*/


void	ft_perror1(const char *cmd, const char *msg, int errno)
{
	//printf("bash: %s: %s\n", cmd, msg);
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_info.exit_status = errno;
}

void	ft_perror2(const char *cmd, const char *arg, const char *msg, int errno)
{
	//printf("bash: %s: %s: %s\n", cmd, arg, msg);
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_info.exit_status = errno;
}
