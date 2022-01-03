/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 18:34:19 by haseo             #+#    #+#             */
/*   Updated: 2022/01/03 17:40:33 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin_on_child(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "pwd")
	|| !ft_strcmp(cmd, "env"))
		return (1);
	return (0);
}

static int is_builtin_on_parent(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "export")
	|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

void exec_builtin(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->argv[0], "cd"))
		ft_cd(cmd);
	else if (!ft_strcmp(cmd->argv[0], "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd->argv[0], "env"))
		ft_env(cmd);
	else if (!ft_strcmp(cmd->argv[0], "export"))
		ft_export(cmd);
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		ft_unset(cmd);
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		ft_exit();
}

char		*get_cmd_path(char *cmd)
{
	char		**paths;
	char		*_cmd;
	char		*cmd_path;
	int			i;
	struct stat	st;

	if (stat(cmd, &st) == 0)
		return (cmd);
	paths = ft_split(get_env(g_info.envp, "PATH"), ':');
	_cmd = ft_strdup("/");
	_cmd = ft_strjoin(_cmd, cmd);
	i = -1;
	while (paths[++i])
	{
		cmd_path = ft_strdup(paths[i]);
		cmd_path = ft_strjoin(cmd_path, _cmd);
		if (stat(cmd_path, &st) == 0)
			break ;
		free(cmd_path);
		cmd_path = NULL;
	}
	ft_free2d(paths);
	free(_cmd);
	return (cmd_path);
}

void		exec_cmd_child(t_cmd *cmd)
{
	char	*cmd_path;

	if (is_builtin_on_child(cmd->argv[0]))
		exec_builtin(cmd);
	else
	{
		cmd_path = get_cmd_path(cmd->argv[0]);
		if (!cmd_path)
			ft_perror3(cmd->argv[0], "command not found", 127);
		else
		{
			if (execve(cmd_path, cmd->argv, g_info.envp) == -1)
					ft_perror("execve", 1);
			free(cmd_path);
		}
	}
}

/*
	AA=1 형태의 new를 쉘 변수 리스트에 추가

	0. 초기 상태인 shell=NULL일 때의 동작을 분리

	- 일반적인 경우-
	1. new_envp를 기존 envp의 size+1 만큼 동적할당하여 기존의 envp를 복사하고, 마지막 항에 new를 할당
	2. g_info.envp에 new_envp를 저장
	3. 기존의 envp를 free
*/

void add_shell_new(char **shell, char *new)
{
	int		i;
	int		j;
	char	**new_shell;

	if (!shell)
	{
		new_shell = (char **)malloc(sizeof(char *) * 2);
		new_shell[0] = ft_strdup(new);
		new_shell[1] = NULL;
		g_info.shell = new_shell;
		return ;
	}
	i = 0;
	while (shell[i])
		i++;
	new_shell = (char **)malloc(sizeof(char *) * (i + 1));
	j = 0;
	while (j < i)
	{
		new_shell[j] = shell[j];
		j++;
	}
	new_shell[j] = ft_strdup(new);
	new_shell[j + 1] = NULL;
	g_info.shell = new_shell;
	free(shell);
}

/*
	AA=123 형식의 str를 쉘 변수 리스트에 추가

	1. str에서 key를 분리하여 쉘 변수 리스트에서 key가 존재하는지 검사
		1-1. 이미 같은 key가 존재한다면, 해당 key의 value를 새로운 value로 대체
		1-2. key가 존재하지 않는다면 새롭게 추가 (add_shell_new())
*/

void add_shell(char **shell, char *str)
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
	old_value = get_shell(&g_info, key);
	if (old_value)
		mod_shell(g_info.shell, key, new_value);
	else
		add_shell_new(g_info.shell, str);
	free(key);
}

void		exec_cmd(t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	if (is_builtin_on_parent(cmd->argv[0]))
		exec_builtin(cmd);
	else if (cmd->shell_var)
	{
		// add_shell_env(cmd->argv[0]);
		add_shell(g_info.shell, cmd->argv[0]);
#ifdef TEST
		printf("[shell list]\n");
		print_shell(g_info.shell);		// SHELL=/bin/bash 첫항에 존재
#endif
	}
	else
	{
		pid = fork();
		if (pid < 0)
			ft_perror("fork", 1);
		else if (pid == 0)
		{
			if (cmd->redirection)
				set_redirection(cmd);
			exec_cmd_child(cmd);
			exit(g_info.exit_status);
		}
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				g_info.exit_status = WEXITSTATUS(status);
			else
				g_info.exit_status = 1;
		}
	}
}
