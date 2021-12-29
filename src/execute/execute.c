/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 18:10:49 by haseo             #+#    #+#             */
/*   Updated: 2021/12/28 17:43:32 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	test 진행 상황
	(에러 발견 시 적어주세요!)

	(1)ft_cd()	: Good

	(2)ft_echo() : Good

	(3)ft_pwd() : Good

	(4)ft_env()

		- argument 주어졌을 때 구현 안함
			-> envp 를 subshell에게 전달하는 과정 필요...
			-> 지금까지의 환경 변수 리스트를 char ** 형식으로 만들어서 subshell에 전달하는 방법?
			-> 아니면 다른 방법?

		- export나 unset 명령어 사용 후, env 명령어 입력시 아래처럼 문자열이 깨지는 현상 발생

			(ex 1)
			/home/shw2662/42Seoul/MiniShell$ unset AA

			/home/shw2662/42Seoul/MiniShell$ env

				----Parsing test----
				input : en��Uv
				argv[0] : en��Uv
				argc = 1
				--------------------

			(ex 2)
			/home/shw2662/42Seoul/MiniShell$ export 1 2 $

			----Parsing test----
			input : export 1 2 $
			argv[0] : export
			argv[1] : 1
			argv[2] : 2
			argv[3] : $
			argc = 4
			--------------------
			bash: export: `3': not a valid identifier
			/home/shw2662/42Seoul/MiniShell$ env

			----Parsing test----
			input : enToUv
			argv[0] : enToUv
			argc = 1
			--------------------

		**hyejung 추가
		기존에 사용했던 명령어랑 겹쳐서 출력이 되는 것 같아요!
		그런데 아래 키 몇번 누르니까 잘 작동은 해요

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


/*
	exec_input 기능

	input으로 들어와 파싱된 cmd list를 순차적으로 실행

	- free_cmd()
		- 만약, readline()을 사용한다면 필요
		- 만약, prompt4()를 사용하여 history를 추가적으로 구현해야 한다면, cmd를 free해서는 안 될 것 같음
*/

void exec_input(t_cmd *cmd)
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
	//free_cmd(cmd);		// 만약, cmd list를 history로 사용한다면, free 하면 안됨
}
