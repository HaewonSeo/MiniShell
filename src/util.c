/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 00:28:18 by haseo             #+#    #+#             */
/*   Updated: 2021/12/22 18:23:47 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// error msg 출력 & exit status 저장 & exit
void ft_perror(const char *str, int errnum)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_info.exit_status = errnum;
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

(3)
shw2662@DESKTOP-F8LA849:~/42Seoul/minishell2$ asaaaa
asaaaa: command not found

*/


void	ft_perror1(const char *cmd, const char *msg, int errnum)
{
	//printf("bash: %s: %s\n", cmd, msg);
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_info.exit_status = errnum;
}

void	ft_perror2(const char *cmd, const char *arg, const char *msg, int errnum)
{
	//printf("bash: %s: %s: %s\n", cmd, arg, msg);
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_info.exit_status = errnum;
}

void	ft_perror3(const char *cmd, const char *msg, int errnum)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_info.exit_status = errnum;
}
