/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 22:24:47 by haseo             #+#    #+#             */
/*   Updated: 2022/01/02 20:47:17 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_l(char *fname)
{
	int	fd;

	fd = open(fname, O_RDONLY);
	if (fd < 0)
		ft_perror1(fname, "No such file or directory", (int)EPERM);
	else
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			ft_perror("dup2", 1);
		close(fd);
	}
}

static void	set_ll(char *delimiter)
{
	int	fd;
	char *input;

	fd = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0744);
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
		set_l("tmp");
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

static void	set_rr(char *fname)
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

void		set_redirection(t_cmd *cur)
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
