/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 18:44:06 by haseo             #+#    #+#             */
/*   Updated: 2022/01/02 17:24:57 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	declare_envp(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		printf("declare -x %s\n", envp[i]);
}

void	ft_export(t_cmd *cmd)
{
	int		i;
	char	*num_str;
	char	*i_str;

	g_info.exit_status = 0;
	if (cmd->argc == 1)
		declare_envp(g_info.envp);
	else
	{
		i = 0;
		while (++i < cmd->argc)
		{
			if (!ft_strcmp(cmd->argv[i], "$"))
				ft_perror2("export", "`$'", "not a valid identifier", 1);
			// $ A=1 형식
			else if (ft_strchr(cmd->argv[i], '=') != NULL)
				add_envp(&g_info, cmd->argv[i]);		// (에러) 같은 값이 중복으로 추가됨
			// $ A 형식
				// add_shell_env(cmd->argv[i]); // (에러) 환경변수 리스트에 A가 추가되지 않음
				// 쉘 변수 리스트에서 먼저 찾고 없으면 널값을 환경변수 리스트에 추가
				// 정확히는 env 명령에는 A가 출력되지는 않으나, export 명령어 입력시 declare -x A 로 출력됨
				// 일단은 env 및 export 시 모두 A가 출력되도록 구현
			else
				add_shell_env(cmd->argv[i]);
		}
	}
}
