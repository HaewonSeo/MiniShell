/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 21:15:34 by haseo             #+#    #+#             */
/*   Updated: 2022/01/02 21:15:45 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd(t_cmd *tmp, char *input)
{
	int n;
	int i;

	n = 0;
	printf("\n----Parsing test----\n");
	printf("input : %s\n", input);
	while (tmp)
	{
		printf("[cmd %d]\n", n++);
		i = -1;
		while (tmp->argv[++i])
			printf("argv[%d] : %s\n", i, tmp->argv[i]);
		printf("argc = %d\n", tmp->argc);
		printf("fd[0] : %d\n", tmp->fd[0]);
		printf("fd[1] : %d\n", tmp->fd[1]);
		printf("pipe = %d\n", tmp->pipe);
		printf("pipe_prev = %d\n", tmp->pipe_prev);
		printf("redirection = %d\n", tmp->redirection);
		printf("shell_var = %d\n", tmp->shell_var);
		printf("quote = %d\n", tmp->quote);
		printf("l = %s\n", tmp->redir->l);
		printf("ll = %s\n", tmp->redir->ll);
		printf("r = %s\n", tmp->redir->r);
		printf("rr = %s\n", tmp->redir->rr);
		printf("--------------------\n");
		tmp = tmp->next;
	}
}
