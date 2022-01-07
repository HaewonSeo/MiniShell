/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 00:28:18 by haseo             #+#    #+#             */
/*   Updated: 2022/01/07 15:40:15 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_perror(char *str, int errnum)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_info.exit_status = errnum;
}

void	ft_perror1(char *cmd, char *msg, int errnum)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_info.exit_status = errnum;
	exit(errnum);
}

void	ft_perror2(char *cmd, char *arg, char *msg, int errnum)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_info.exit_status = errnum;
	exit(errnum);
}

void	ft_perror3(char *cmd, char *msg, int errnum)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_info.exit_status = errnum;
	exit(errnum);
}

void	ft_perror4(char *cmd, int i, char *msg, int errnum)
{
	char	*num_str;
	char	*i_str;

	num_str = ft_strdup("`");
	i_str = ft_itoa(i);
	num_str = ft_strjoin(num_str, i_str);
	num_str = ft_strjoin(num_str, "\'");
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(num_str, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free(i_str);
	free(num_str);
	g_info.exit_status = errnum;
	exit(errnum);
}
