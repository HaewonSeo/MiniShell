/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 18:43:46 by haseo             #+#    #+#             */
/*   Updated: 2021/12/15 18:49:13 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	각 static 함수 마지막에 추가해야 할 기능

	1. 환경변수 PWD의 value를 갱신해야 함
		-> 해당 기능을 수행하는 함수(mod_env()) 필요
	else
	{
		char *new_value = getcwd();
		mod_env(g_info.head_env, new_value);
	}

	2. get_env()로 받아온 path는 free()해주어야 함
	if (path)
		free(path);
*/

static void cd_home()
{
	char	*path;

	path = get_env(g_info.head_env, "HOME");
	if (!path || chdir(path) == -1)
		ft_perror1("cd", "No $HOME", EPERM);
}

static void cd_envv(const char *arg)
{
	char	*path;

	path = get_env(g_info.head_env, &arg[1]);
	if (!path || chdir(path) == -1)
		ft_perror2("cd", arg, "No such argument", EPERM);
}

static void cd_path(const char *path)
{
	if (!path || chdir(path) == -1)
		ft_perror2("cd", path, "No such file or directory", EPERM);
}


/*
ft_cd() 기능

1. argument에 따른 cd 이동

	1) `cd ` or `cd ~` : HOME 으로 cd
	2) 환경변수 경로로 cd
	3) 일반적인 경로로 cd

2. 환경변수 PWD 값 변경

*/
void ft_cd(t_cmd *cmd)
{
	if (cmd->argc != 2)
		ft_perror1("cd", "too many arguments", EPERM);
	else if (cmd->argc == 1 || !ft_strcmp(cmd->argv[1], "~"))
		cd_home();
	else if (cmd->argc == 2 && cmd[1][0] == '$')
		cd_envv(cmd->argv[1]);
	else if (cmd->argc == 2 && cmd[1][0] != '~' && cmd[1][0] != '$')
		cd_path(cmd->argv[1]);
	else
		ft_perror2("cd", cmd->argv[1], "No such file or directory", EPERM);
}
