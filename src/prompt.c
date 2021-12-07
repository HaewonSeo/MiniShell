/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 22:11:54 by haseo             #+#    #+#             */
/*   Updated: 2021/12/07 16:38:56 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// readline 사용하여 input을 받는 방법
void prompt2()
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

// GNL을 사용하여 input을 받는 방법
void prompt3()
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
}

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
	}
	else
	{
		str = (char *)ft_calloc(ft_strlen(s) + 1, sizeof(char));
		if (!str)
			exit(1);
		while (s[++i])
			str[i] = s[i];
		str[i] = ch;
		free(s);
	}
	return (str);
}

// char 1개씩 input을 받는 방법
void prompt4()
{
	int		ch;
	char	*cmd;

	ch = 0;
	cmd = NULL;
	ft_putstr_fd(getcwd(NULL, 0), STDOUT_FILENO);
	ft_putstr_fd("$ ", STDOUT_FILENO);
	while (read(STDIN_FILENO, &ch, 1))
	{
		// ft_putchar_fd((char)ch, STDOUT_FILENO);
		if (ft_isprint(ch))
			cmd = ft_str_add_back(cmd, (char)ch);
		else if (ch == LF)
			break;
		// 입력이 없을 때, Ctrl + D 누르면 minishell 종료
		else if (!cmd && ch == EOT)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			ft_exit2(1);
		}
	}
	printf("cmd : %s\n", cmd);
	free(cmd);
}
