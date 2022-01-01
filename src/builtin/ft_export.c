/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 18:44:06 by haseo             #+#    #+#             */
/*   Updated: 2022/01/01 20:22:18 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

	export 기능

	1. argument가 없는 경우
		-> 모든 쉘 변수를 환경변수 리스트에 추가하는 것이 아니라
		-> declare -x 출력과 함께 모든 환경변수를 출력
		(declare -x : 스크립트 외부에서도 해당 변수를 사용할 수 있게 함)

	2. argument로 쉘 변수가 주어지는 경우
		1) 쉘 변수가 이미 존재하는 경우 쉘 변수를 환경변수 리스트에 추가
			$ export AA (AA는 이미 쉘 변수로 존재)
		2) 쉘 변수가 존재하지 않는 경우 아무 동작도 하지 않는다.
			$ export AA (AA가 없는 경우)
		3) AA=123 형식의 경우
			$ export AA=123
			-> 쉘 변수 리스트에 추가 (에러) 쉘변수 리스트에 추가되지 않음
			-> 환경변수 리스트에도 추가

	- 에러 출력 예 ($로 시작하는 arg는 에러로 출력되고, 나머지 arg는 정상적으로 환경변수 리스트에 추가됨)
		shw2662@DESKTOP-F8LA849:~$ export A $B
		bash: export: `2': not a valid identifier

		`2' 형식으로 출력되기 때문에 해당 형식을 갖춘 string 을 만들어야 함

	- 쉘 변수 출력 명령어(실제 bash에서 동작, minishell에서는 동작 안함)
		$ compgen -A variable
*/

static void declare_envp(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		printf("declare -x %s\n", envp[i]);
}

void ft_export(t_cmd *cmd)
{
	int		i;
	char	*num_str;
	char	*i_str;

	if (cmd->argc == 1)
		declare_envp(g_info.envp);
	else
	{
		i = 0;
		while (++i < cmd->argc)
		{
			if (cmd->argv[i][0] == '$')	// 변수가 $ABC 형식으로 주어지는 경우 -> 에러처리
			{
				num_str = ft_strdup("`");
				i_str = ft_itoa(i);
				num_str = ft_strjoin(num_str, i_str);
				num_str = ft_strjoin(num_str, "\'");
				ft_perror2("export", num_str, "not a valid identifier");
				free(i_str);
				free(num_str);
			}
			// $ A=1 형식
			else if (ft_strchr(cmd->argv[i], '=') != NULL)
				add_envp(&g_info, cmd->argv[i]);		// (에러) 같은 값이 중복으로 추가됨
			// $ A 형식
				// 쉘 변수 리스트에서 먼저 찾고 없으면 널값을 환경변수 리스트에 추가
				// 정확히는 env 명령에는 A가 출력되지는 않으나, export 명령어 입력시 declare -x A 로 출력됨
				// 일단은 env 및 export 시 모두 A가 출력되도록 구현
				// (에러) 환경변수 리스트에 A가 추가되지 않음
			else
				add_shell_env(cmd->argv[i]);
		}
	}
}
