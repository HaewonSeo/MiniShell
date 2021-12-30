/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:30:07 by haseo             #+#    #+#             */
/*   Updated: 2021/12/30 21:10:07 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("SIGINT : print a new prompt on a newline.\n");
		g_info.exit_status = 130;
	}
	else if (signum == SIGQUIT)
	{
		printf("SIGQUIT : DO NOTHING.\n");
	}
}

void get_canonical_mode()
{
	char	*term;

	tcgetattr(STDIN_FILENO, &g_info.term.canonical);
	term = "xterm";
	term = getenv("TERM");
	tgetent(NULL, "xterm");
	g_info.term.cm = tgetstr("cm", NULL);
	g_info.term.ce = tgetstr("ce", NULL);
}

void set_noncanonical_mode()
{
	tcgetattr(STDIN_FILENO, &g_info.term.noncanonical);
	g_info.term.noncanonical.c_lflag &= ~(ICANON | ECHO);
	g_info.term.noncanonical.c_cc[VMIN] = 1;
	g_info.term.noncanonical.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &g_info.term.noncanonical);
}

void set_canonical_mode()
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_info.term.canonical);
}

static void init_info(char *argv[], char *envp[])
{
	g_info.argv = argv;
	g_info.envp = envp;
	g_info.head_env = (t_env *)ft_calloc(1, sizeof(t_env)); // head는 더미 포인터
	g_info.head_cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	split_envp(envp, &g_info);
#ifdef TEST11
	print_envp(g_info.envp);
#endif
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*input;
	t_cmd	*cur;
	int		i;

	signal(SIGINT, (void *)signal_handler);
	signal(SIGQUIT, (void *)signal_handler);
	//get_canonical_mode();
	//set_noncanonical_mode();
	init_info(argv, envp);

	cur = g_info.head_cmd;
	while (1)
	{
		input = prompt();
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

	//set_canonical_mode();
	return 0;
}
