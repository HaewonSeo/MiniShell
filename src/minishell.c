/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:30:07 by haseo             #+#    #+#             */
/*   Updated: 2021/12/07 16:44:11 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		// prompt();
		printf("SIGINT : print a new prompt on a newline.\n");
		exit(1);
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
	tcsetattr(STDIN_FILENO, TCSANOW, &g_info->term.noncanonical);
}

void set_canonical_mode()
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_info.term.canonical);
}

int	main(int argc, char *argv[], char *envp[])
{

	signal(SIGINT, (void *)signal_handler);
	signal(SIGQUIT, (void *)signal_handler);
	//get_canonical_mode();
	//set_noncanonical_mode();
	while (1)
		prompt2();

	//set_canonical_mode();
	return 0;
}
