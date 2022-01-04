/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 22:11:54 by haseo             #+#    #+#             */
/*   Updated: 2022/01/04 15:41:13 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prompt(void)
{
	char	*cwd;
	char	*cmd;

	cwd = ft_strdup(BLU);
	cwd = ft_strjoin(cwd, getcwd(NULL, 0));
	cwd = ft_strjoin(cwd, "$ ");
	cwd = ft_strjoin(cwd, EOC);
	cmd = readline(cwd);
	if (!cmd)
	{
		free(cwd);
		ft_exit();
	}
	printf("%s\n", cmd);
	add_history(cmd);
	free(cwd);
	return (cmd);
}

/*
static char	*ft_str_add_back(char *s, char ch)
{
	char	*str;
	int		i;

	i = -1;
	if (!s)
	{
		str = (char *)ft_calloc(2, sizeof(char));
		if (!str)
			exit(1);
		str[0] = ch;
		str[1] = '\0';
	}
	else
	{
		str = (char *)ft_calloc(ft_strlen(s) + 1, sizeof(char));
		if (!str)
			exit(1);
		while (s[++i])
			str[i] = s[i];
		str[i] = ch;
		str[i + 1] = '\0';
		free(s);
	}
	return (str);
}

static void	ft_str_remove_back(char *s)
{
	int	len;

	len = ft_strlen(s);
	s[len - 1] = '\0';
}


	cwd 출력 시 , cwd 길이만큼 cursor의 col값이 증가하지 않아서 cursor 제어에 오류가 발생함
	ft_putstr_fd(BLU, STDOUT_FILENO);
	ft_putstr_fd(getcwd(NULL, 0), STDOUT_FILENO);
	ft_putstr_fd("$ ", STDOUT_FILENO);
	ft_putstr_fd(EOC, STDOUT_FILENO);

char	*prompt4(void)
{
	int		ch;
	char	*input;
	int		col = 0;
	int		row = 0;

	ch = 0;
	input = NULL;
	get_cursor_pos(&col, &row);
	while (read(STDIN_FILENO, &ch, sizeof(ch)) > 0)
	{
		if (g_info.signal)
		{
			g_info.signal = 0;
			if (input)
				free(input);
			return (NULL);
		}
		if (ft_isprint(ch))
		{
			col++;
			input = ft_str_add_back(input, (char)ch);
			ft_putchar_fd(ch, STDOUT_FILENO);
		}
		else if (ch == DEL)
		{
			put_backspace(&col, &row);
			ft_str_remove_back(input);
		}
		else if (ch == LEFT_ARROW)
			move_cursor_left(&col, &row);
		else if (ch == RIGHT_ARROW)
			move_cursor_right(&col, &row);
		else if (ch == LF)
			break ;
		else if (!input && ch == EOT)
			ft_exit();
		ch = 0;
	}
	return (input);
}
*/
