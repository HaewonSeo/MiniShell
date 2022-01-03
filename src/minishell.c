/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:30:07 by haseo             #+#    #+#             */
/*   Updated: 2022/01/03 17:15:59 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_info(int argc, char *argv[], char *envp[])
{
	g_info.argc = argc;
	g_info.argv = argv;
	g_info.envp = envp;
	g_info.head_cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	// g_info.shell = (char **)malloc(sizeof(char *) * 1);
	g_info.shell = NULL;
	g_info.shell_len = 0;
	split_envp(envp, &g_info);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*input;
	t_cmd	*cur;

	signal(SIGINT, (void *)signal_handler);
	signal(SIGQUIT, (void *)signal_handler);
#ifdef WSL
	get_canonical_mode();
	set_noncanonical_mode();
#endif
	init_info(argc, argv, envp);
	cur = g_info.head_cmd;
	while (1)
	{
#ifdef WSL
		input = prompt4();
#else
		input = prompt();
#endif
		if (!input)
			continue;
		parsing_cmd(input, &cur);
		cur = cur->next;
#ifdef TEST
		print_cmd(cur, input);
#endif
		exec_input(cur);
		free(input);
		input = NULL;
	}
	return 0;
}
