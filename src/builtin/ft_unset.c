/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 18:44:18 by haseo             #+#    #+#             */
/*   Updated: 2022/01/01 20:23:02 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	unset 기능

	1. env list에서 `$`기호 없이 arg로 주어지는 환경변수 key-value 삭제
	2. 쉘 변수도 삭제 - 쉘 변수 리스트를 생성해야 할지 고민이고, 아직 작성한 함수는 아닙니다.


	- 에러 출력 예 (export와 동일)
		shw2662@DESKTOP-F8LA849:~$ unset $A B
		bash: unset: `1': not a valid identifier

		`1' 형식으로 출력되기 때문에 해당 형식을 갖춘 string 을 만들어야 함 -> 함수화할지 고민
*/

void ft_unset(t_cmd *cmd)
{
	int		i;
	char	*num_str;
	char	*i_str;

	i = 0;
	while (++i < cmd->argc)
	{
		if (cmd->argv[i][0] == '$')
		{
			num_str = ft_strdup("`");
			i_str = ft_itoa(i);
			num_str = ft_strjoin(num_str, i_str);
			num_str = ft_strjoin(num_str, "\'");
			ft_perror2("export", num_str, "not a valid identifier");
			free(i_str);
			free(num_str);
		}
		else
		{
			del_envp(&g_info, cmd->argv[i]);
			// del_shell(&g_info, cmd->argv[i]); (에러) 동작안하고 무한루프 빠짐
#ifdef TEST
			printf("[shell list]\n");		// (에러) 쉘 변수 리스트에 환경변수 SHELL이 존재함
			print_shell(g_info.shell);		// SHELL=/bin/bash 첫항에 존재
#endif
		}
	}
	g_info.exit_status = 0;
}
