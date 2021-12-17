/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:30:07 by haseo             #+#    #+#             */
/*   Updated: 2021/12/17 20:45:26 by haseo            ###   ########.fr       */
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
	tcgetattr(STDIN_FILENO, &g_info.term.canonical);
}

void set_noncanonical_mode()
{
	tcgetattr(STDIN_FILENO, &g_info.term.noncanonical);
	g_info.term.noncanonical.c_lflag &= ~(ICANON);
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
	split_env(envp, &(g_info.head_env));
#ifdef TEST11
	print_env(g_info.head_env);
#endif
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*input;
	t_cmd	*cur;
	int		i;

	signal(SIGINT, (void *)signal_handler);
	signal(SIGQUIT, (void *)signal_handler);
	get_canonical_mode();
	set_noncanonical_mode();
	init_info(argv, envp);

	cur = g_info.head_cmd;
	while (1)
	{
		input = prompt4();
		parsing_cmd(input, &cur);
		cur = cur->next;

#ifdef TEST
		printf("\n----Parsing test----\n");
		printf("input : %s\n", input);
		i = 0;
		while (cur->argv[i])
		{
			printf("argv[%d] : %s\n", i, cur->argv[i]);
			i++;
		}
		printf("argc = %d\n", cur->argc);
		printf("--------------------\n");
#endif

		exec_cmd(cur);
		free(input);
	}

	set_canonical_mode();

	return 0;
}
