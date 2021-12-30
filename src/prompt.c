/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 22:11:54 by haseo             #+#    #+#             */
/*   Updated: 2021/12/30 21:13:52 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// readline 사용하여 input을 받는 방법
void  *prompt2()
{
	char	*cwd;
	char	*cmd;

	cwd = getcwd(NULL, 0);	// dynamic allocation
	cwd = ft_strjoin(cwd, "$ ");
	while (1)
	{
		cmd = readline(cwd);
		if (cmd)
			printf("%s\n", cmd);
		else
			break;
		add_history(cmd);	// history에 저장(위, 아래 방향키로 확인 가능)
		free(cmd);
	}
	free(cwd);
}

char	*prompt()
{
	char	*cwd;
	char	*cmd;

	cwd = getcwd(NULL, 0);	// dynamic allocation
	cwd = ft_strjoin(cwd, "$ ");
	cmd = readline(cwd);
	if (!cmd)
	{
		free(cwd);
		ft_exit();
	}
	printf("%s\n", cmd);
	add_history(cmd);	// history에 저장(위, 아래 방향키로 확인 가능)
	free(cwd);
	return (cmd);
}


// GNL을 사용하여 input을 받는 방법
/*void prompt3()
{
	char	*cmd;
	char	*line;
	int		rsize;

	ft_putstr_fd(getcwd(NULL, 0), STDOUT_FILENO);
	ft_putstr_fd("$ ", STDOUT_FILENO);
	while (1)
	{
		rsize = get_next_line(STDIN_FILENO, &line);
		if (line[0] == EOT)
			exit(0);
		printf("%d %s\n", rsize, line);
		free(line);
		return ;

		cmd = ft_strjoin(cmd, line);
		free(line);
		if (rsize <= 0)
			break;
	}
	printf("%s ", cmd);
	free(cmd);
}*/

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

// 백스페이스 입력시 input의 마지막 한 글자가 지워짐
static void *ft_str_remove_back(char *s)
{
	int	len;

	len = ft_strlen(s);
	s[len - 1] = '\0';
}

// char 1개씩 input을 받는 방법
char *prompt4()
{
	int		ch;
	char	*input;
	int		col = 0;
	int		row = 0;

	ch = 0;
	input = NULL;

	// cwd 출력 시 , cwd 길이만큼 cursor의 col값이 증가하지 않아서 cursor 제어에 오류가 발생함
	// 이 오류를 제외하고는 정상적으로 동작함

	// ft_putstr_fd(BLU, STDOUT_FILENO);
	// ft_putstr_fd(getcwd(NULL, 0), STDOUT_FILENO);
	// ft_putstr_fd("$ ", STDOUT_FILENO);
	// ft_putstr_fd(EOC, STDOUT_FILENO);

	get_cursor_pos(&col, &row);
	while (read(STDIN_FILENO, &ch, sizeof(ch)) > 0)
	{

		// ft_putchar_fd((char)ch, STDOUT_FILENO);
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
		// 입력이 없을 때, Ctrl + D 누르면 minishell 종료
		else if (!input && ch == EOT)
			ft_exit();
		ch = 0;
	}
	return (input);
}
