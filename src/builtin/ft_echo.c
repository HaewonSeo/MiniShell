/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:04:50 by haseo             #+#    #+#             */
/*   Updated: 2021/12/15 19:07:35 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void echo_envv(char *arg)
{
	char	*key;
	char	*value;

	if (arg[1] == '?')
		printf("%d", g_info.exit_statue);
	else
	{
		key = &arg[1];
		// 환경변수 리스트에서 key에 해당하는 value를 찾아서 출력
		value = get_env(g_info.head_env, key);
		if (value)
		{
			printf("%s", value);
			free(value);
		}
	}
}

/*
	echo 기능

	1. 옵션 -n이 있는 경우 개행 출력하지 않음
	2. 일반적인 경우 argument 출력
	3. 환경변수 출력 (환경변수가 존재하지 않는 경우 출력하지 않음)
		출력 예(ASDD는 존재하지 않는 환경변수)
		shw2662@DESKTOP-F8LA849:~$ echo $ASDD A B
		A B

*/
void ft_echo(t_cmd *cmd)
{
	bool	opt_n;
	int		i;

	opt_n = false;
	i = 0;
	if (!strcmp(cmd->argv[1], "-n"))
	{
		opt_n = true;
		++i;
	}
	while (++i < cmd->argc)
	{
		if (cmd->argv[i][0] == '$')
			echo_envv(cmd->argv[i]);
		else
			printf("%s", cmd->argv[i]);
		if (i < cmd->argc - 1)
			printf(" ");
	}
	if (!opt_n)
		printf("\n");
}
