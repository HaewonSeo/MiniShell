/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 18:10:49 by haseo             #+#    #+#             */
/*   Updated: 2022/01/02 00:13:56 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	test 진행 상황
	(에러 발견 시 적어주세요!)

	(1)ft_cd()	: Good

	(2)ft_echo() : Good

	(3)ft_pwd() : Good

	(4)ft_env() : Good

	(5)ft_export()

		- 쉘 변수를 환경 변수 리스트에 추가하는 기능을 구현하지 못함
			- prompt에서 쉘변수를 추가하는 명령을 받는 기능을 구현해야 함
				(ex 1)
				$ AA=123 // AA라는 쉘변수에 123을 대입
				$ export AA // 쉘 변수가 존재해야 AA가 비로소 env에 추가됨

				(ex 2)
				$ export AAAAA=4	// ex1 과 동일한 기능


	**hyejung

	- 쉘변수가 존재해도, 값이 바뀌지 않음
	ex)
	USER=jeonghyeonjin
	$ export USER=hyejung
	-> 결과 확인시 변경되지 않음을 알 수 있음


	(6)ft_unset() : Good

	(7)ft_exit() : Good

*/

/*
	특이 사항

	- pipe 기호 다음 cmd가 존재하지 않는 경우는 일단 에러로 처리하기로 함
		ex) $ ls -l |


	- 실행 예
		$ ls | sort
		$ ls -l | sort
		$ env | sort			// -> 오류 ...
		$ ls | grep ab | sort
		$ ls | grep ab | sort -r // -> 오류 -에

	- builtin에 대한 pipe와 redirection 처리 필요

*/

void	exec_input(t_cmd *cmd)
{
	t_cmd	*cur;

	cur = cmd;
	while (cur)
	{
		if (cur->pipe || cur->pipe_prev)
			exec_pipe(cur);
		else
			exec_cmd(cur);
		cur = cur->next;
	}
}
