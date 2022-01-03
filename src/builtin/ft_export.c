/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 18:44:06 by haseo             #+#    #+#             */
/*   Updated: 2022/01/03 17:40:33 by haseo            ###   ########.fr       */
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

/*

	AA=1 형태의 new를 envp에 추가

	1. new_envp를 기존 envp의 size+1 만큼 동적할당하여 기존의 envp를 복사하고, 마지막 항에 new를 할당
	2. g_info.envp에 new_envp를 저장
	3. 기존의 envp를 free
*/

void add_env_new(char **envp, char *new)
{
	int		i;
	int		j;
	char	**new_envp;

	i = 0;
	while (envp[i])
		i++;
	new_envp = (char **)malloc(sizeof(char *) * (i + 1));
	j = 0;
	while (j < i)
	{
		new_envp[j] = envp[j];
		j++;
	}
	new_envp[j] = ft_strdup(new);
	new_envp[j + 1] = NULL;
	g_info.envp = new_envp;
	free(envp);
}

/*
	AA=123 형식의 str를 envp에 추가

	1. str에서 key를 분리하여 현재 envp에 존재하는지 검사
		1-1. 이미 같은 key가 존재한다면, 해당 key의 value를 새로운 value로 대체
		1-2. key가 존재하지 않는다면 새롭게 추가 (add_env_new())

	2. 쉘 변수리스트에서 key 값을 가진 쉘 변수를 삭제
		- 존재 유무에 따른 처리는 del_shell()에서 판단

*/

void add_env(char **envp, char *str)
{
	char	*key;
	char	*old_value;
	char	*new_value;
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			break;
	}
	if (i == 0)
		i++;
	key = ft_substr(str, 0, i);
	new_value = ft_strchr(str, '=');
	old_value = get_env(g_info.envp, key);
	if (old_value)
		mod_env(g_info.envp, key, new_value);
	else
		add_env_new(g_info.envp, str);
	del_shell(&g_info, key);
	free(key);
}

/*
	A 형식의 key를 envp에 추가

	1. key가 이미 환경변수 리스트에 존재하는 경우, 아무 동작도 하지 않음
		// (생략)이미 환경변수에 NULL의 변수 가 있는지 확인해봐야 함

	2. key가 쉘 변수 리스트에 존재하는 경우, 그 값을 찾아 envp에 추가

	3. key가 쉘 변수 리스트에 존재하지 않는 경우, 널값의 A를 envp에 추가

	4. 쉘 변수리스트에서 key 값을 가진 쉘 변수를 삭제

*/

void add_shell_to_envp(char **envp, char *key)
{
	char	*shell_value;
	char	*new;

	if (get_env(g_info.envp, key))
		return ;
	shell_value = get_shell(&g_info, key);
	if (shell_value)
	{
		new = ft_strdup(key);
		new = ft_strjoin(new, "=");
		new = ft_strjoin(new, shell_value);
		add_env_new(g_info.envp, new);
	}
	else
		add_env_new(g_info.envp, key);
	del_shell(&g_info, key);
}

void	ft_export(t_cmd *cmd)
{
	int		i;

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
				add_env(g_info.envp, cmd->argv[i]);
			// $ A 형식
			else
				add_shell_to_envp(g_info.envp, cmd->argv[i]);
		}
	}
}
