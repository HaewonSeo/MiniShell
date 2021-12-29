/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 20:12:27 by haseo             #+#    #+#             */
/*   Updated: 2021/12/29 21:46:41 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_nbrlen(int n)
{
	int		len;

	len = 0;
	if (len <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

/*
	get_cursor_cur_pos() : 현재 커서의 좌표를 얻는다.

	1. 커서 위치를 STDIN에 기록, 커서 위치는 [row;colR 형식으로 기록된다.
		- 이 때 출력될 커서의 위치는 사용할 위치보다 1씩 크다. 따라서 1을 뺀 값을 저장한다.
	2. STDIN을 읽어서 row와 col 값을 파싱
*/
void	get_cursor_pos(int *col, int *row)
{
	int		read_size;
	int		i;
	char	buf[256];
	int		is_row;

	ft_putstr_fd("\033[6n", STDIN_FILENO);
	read_size = read(STDIN_FILENO, buf, 255);
	buf[read_size] = '\0';
	is_row = 1;
	i = 0;
	while (buf[i])
	{
		if (ft_isdigit(buf[i]))
		{
			if (is_row)
			{
				*row = atoi(&buf[i]) - 1;
				i += ft_nbrlen(*row) + 1;
				is_row = 0;
			}
			else
			{
				*col = atoi(&buf[i]) - 1;
				i += ft_nbrlen(*col) + 1;
			}
		}
		else
			i++;
	}
	// printf("col : %d\t row : %d\n", *col, *row);
}

static int	putchar_stdout(int c)
{
	write(STDOUT_FILENO, &c, 1);
	return (0);
}

void	put_backspace(int *col, int *row)
{
	if (*col == 0)
		return ;
	(*col)--;
	tputs(tgoto(g_info.term.cm, *col, *row), 1, putchar_stdout);
	tputs(g_info.term.ce, 1, putchar_stdout);
}

void	move_cursor_left(int *col, int *row)
{
	if (*col == 0)
		return ;
	(*col)--;
	tputs(tgoto(g_info.term.cm, *col, *row), 1, putchar_stdout);
}

void	move_cursor_right(int *col, int *row)
{
	(*col)++;
	tputs(tgoto(g_info.term.cm, *col, *row), 1, putchar_stdout);
}
