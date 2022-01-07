/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:30:07 by haseo             #+#    #+#             */
/*   Updated: 2022/01/07 18:00:09 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_info(int argc, char *argv[], char *envp[])
{
	g_info.argc = argc;
	g_info.argv = argv;
	g_info.envp = envp;
	g_info.head_cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	g_info.shell = NULL;
	g_info.shell_len = 0;
	split_envp(envp, &g_info);
	rl_catch_signals = 0;
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*input;
	t_cmd	*cur;

	signal(SIGINT, (void *)signal_handler);
	signal(SIGQUIT, (void *)signal_handler);
	init_info(argc, argv, envp);
	cur = g_info.head_cmd;
	while (1)
	{
		input = prompt();
		if (!input)
			continue ;
		parsing_cmd(input, &cur);
		cur = cur->next;
		if (cur->argc)
			exec_input(cur);
		free(input);
		input = NULL;
	}
	return (0);
}
