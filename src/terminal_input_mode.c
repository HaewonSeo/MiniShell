/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_input_mode.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 14:25:31 by haseo             #+#    #+#             */
/*   Updated: 2022/01/01 14:25:44 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
