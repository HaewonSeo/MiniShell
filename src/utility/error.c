/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 00:28:18 by haseo             #+#    #+#             */
/*   Updated: 2022/01/02 20:47:39 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_perror(const char *str, int errnum)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_info.exit_status = errnum;
	exit(errnum);
}

void	ft_perror1(const char *cmd, const char *msg, int errnum)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_info.exit_status = errnum;
	exit(errnum);
}

void	ft_perror2(const char *cmd, const char *arg, const char *msg, int errnum)
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

void	ft_perror3(const char *cmd, const char *msg, int errnum)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	g_info.exit_status = errnum;
	exit(errnum);
}

void	ft_perror4(const char *cmd, int i, const char *msg, int errnum)
{
	char	*num_str;
	char	*i_str;

	num_str = ft_strdup("`");
	i_str = ft_itoa(i);
	num_str = ft_strjoin(num_str, i_str);
	num_str = ft_strjoin(num_str, "\'");
	ft_perror2(cmd, num_str, msg, errnum);
	free(i_str);
	free(num_str);
	// exit(errnum);
}
