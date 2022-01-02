/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:30:07 by haseo             #+#    #+#             */
/*   Updated: 2022/01/02 18:09:18 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_info(char *argv[], char *envp[])
{
	g_info.argv = argv;
	g_info.envp = envp;
	g_info.head_cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	g_info.shell = (char **)malloc(sizeof(char *) * 1);
	split_envp(envp, &g_info);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*input;
	t_cmd	*cur;
	int		i;

	signal(SIGINT, (void *)signal_handler);
	signal(SIGQUIT, (void *)signal_handler);
#ifdef WSL
	get_canonical_mode();
	set_noncanonical_mode();
#endif
	init_info(argv, envp);

	cur = g_info.head_cmd;
	while (1)
	{
#ifdef WSL
		input = prompt4();
#else
		input = prompt2();
#endif
		parsing_cmd(input, &cur);
		cur = cur->next;

#ifdef TEST
		t_cmd *tmp = cur;
		printf("\n----Parsing test----\n");
		printf("input : %s\n", input);

		int n = 0;
		while (tmp)
		{
			printf("[cmd %d]\n", n++);
			i = 0;
			while (tmp->argv[i])
			{
				printf("argv[%d] : %s\n", i, tmp->argv[i]);
				i++;
			}
			printf("argc = %d\n", tmp->argc);
			printf("fd[0] : %d\n", tmp->fd[0]);
			printf("fd[1] : %d\n", tmp->fd[1]);
			printf("pipe = %d\n", tmp->pipe);
			printf("pipe_prev = %d\n", tmp->pipe_prev);
			printf("redirection = %d\n", tmp->redirection);
			printf("shell_var = %d\n", tmp->shell_var);
			printf("l = %s\n", tmp->redir->l);
			printf("ll = %s\n", tmp->redir->ll);
			printf("r = %s\n", tmp->redir->r);
			printf("rr = %s\n", tmp->redir->rr);
			printf("--------------------\n");
			tmp = tmp->next;
		}
#endif
		exec_input(cur);
		free(input);
		input = NULL;
	}

#ifdef WSL
	set_canonical_mode();
#endif
	return 0;
}
