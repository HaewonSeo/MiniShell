/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:30:10 by haseo             #+#    #+#             */
/*   Updated: 2021/12/07 16:38:26 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <term.h>
# include "libft.h"
# include "get_next_line.h"
# include <readline/readline.h>
# include <readline/history.h>

#define EOT	4
#define LF	10

typedef struct			s_term {
	struct termios		canonical;
	struct termios		noncanonical;
}						t_term;

typedef struct			s_info {
	t_term				term;
}						t_info;

t_info					g_info;


/*
** terminal
*/

void get_canonical_mode();
void set_noncanonical_mode();
void set_canonical_mode();

/*
** prompt
*/

void prompt2();
void prompt3();
void prompt4();

/*
** utility
*/

void ft_exit2(int errno);


#endif
