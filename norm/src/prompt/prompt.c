/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 22:11:54 by haseo             #+#    #+#             */
/*   Updated: 2022/01/07 17:07:22 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prompt(void)
{
	char	*cwd;
	char	*cmd;

	cwd = ft_strdup(BLU);
	cwd = ft_strjoin(cwd, getcwd(NULL, 0));
	cwd = ft_strjoin(cwd, "$ ");
	cwd = ft_strjoin(cwd, EOC);
	cmd = readline(cwd);
	if (!cmd)
	{
		free(cwd);
		ft_exit();
	}
	add_history(cmd);
	free(cwd);
	return (cmd);
}

char	*prompt_heredoc(void)
{
	char	*cmd;

	cmd = readline("> ");
	if (!cmd)
		ft_exit();
	return (cmd);
}
