/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 18:10:49 by haseo             #+#    #+#             */
/*   Updated: 2021/12/17 21:06:51 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo")
	|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "env")
	|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "export")
	|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

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

	(5)ft_export()

		- 쉘 변수를 환경 변수 리스트에 추가하는 기능을 구현하지 못함
			- prompt에서 쉘변수를 추가하는 명령을 받는 기능을 구현해야 함
				(ex 1)
				$ AA=123 // AA라는 쉘변수에 123을 대입
				$ export AA // 쉘 변수가 존재해야 AA가 비로소 env에 추가됨

				(ex 2)
				$ export AAAAA=4	// ex1 과 동일한 기능


	(6)ft_unset() : Good

	(7)ft_exit() : Good

*/

static void exec_builtin(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->argv[0], "cd"))
		ft_cd(cmd);
	else if (!ft_strcmp(cmd->argv[0], "echo"))
		ft_echo(cmd);//
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		ft_pwd();//
	else if (!ft_strcmp(cmd->argv[0], "env"))
		ft_env(cmd);
	else if (!ft_strcmp(cmd->argv[0], "export"))
		ft_export(cmd);
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		ft_unset(cmd);
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		ft_exit();//
}

void exec_cmd(t_cmd *cur)
{
	if (cur->argv[0])
	{
		if (is_builtin(cur->argv[0]))
			exec_builtin(cur);
		// else if (cur->redirection)
		// 	exec_redirection(cur);
		// else if (cur->pipe)
		// 	exec_pipe(cur);
	}
	// free cmd list
}
