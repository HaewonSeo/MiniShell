/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 18:44:06 by haseo             #+#    #+#             */
/*   Updated: 2021/12/15 18:59:22 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

	export 기능

	쉘 변수를 환경변수 리스트에 추가
		- 쉘 변수가 존재하지 않는 경우 아무 동작도 하지 않는다.

	- shell_var 관련 함수는 아직 작성하지 않았습니다.

	- 에러 출력 예 ($로 시작하는 arg는 에러로 출력되고, 나머지 arg는 정상적으로 환경변수 리스트에 추가됨)
		shw2662@DESKTOP-F8LA849:~$ export A $B
		bash: export: `2': not a valid identifier

		`2' 형식으로 출력되기 때문에 해당 형식을 갖춘 string 을 만들어야 함

*/

static void export_shell_var(const char *shell_var_key)
{
	char	*shell_var_value;

	shell_var_value = NULL;
	shell_var_value = get_shell_var(g_info.head_shell_var, shell_var_key);
	if (shell_var_value)
	{
		add_env(g_info.head_env, shell_var_key, shell_var_value);
		free(shell_var_value);
	}
}

void ft_export(t_cmd *cmd)
{
	int		i;
	char	*num_str;
	char	*i_str;

	i = 0;
	while (++i < cmd->argc)
	{
		if (cmd->argv[i][0] == '$')
		{
			num_str = ft_strdup('`');
			i_str = ft_itoa(i);
			ft_strjoin(num_str, i_str);
			ft_strjoin(num_str, '\'');
			ft_perror2("export", num_str, "not a valid identifier");
			free(i_str);
			free(num_str);
		}
		else
			export_shell_var(cmd->argv[i]);
	}

}
