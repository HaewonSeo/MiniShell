/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 18:34:19 by haseo             #+#    #+#             */
/*   Updated: 2021/12/30 17:37:51 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo")
	|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "env")
	|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "export")
	|| !ft_strcmp(cmd, "unset"))
		return (1);
	return (0);
	//  || !ft_strcmp(cmd, "exit")
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
	// else if (!ft_strcmp(cmd->argv[0], "exit"))
	// 	ft_exit();
	g_info.exit_status = 0;
}

/*
	get_cmd_path() 기능

	환경 변수 path의 모든 경로와 cmd를 순차적으로 연결하여 해당 경로에서 cmd 실행 파일을 찾아본다.
	만약 있다면 해당 cmd의 절대경로를 return
	만약 없다면 NULL return

	0. cmd 자체가 경로로 주어지고, 실행 파일이 존재하는 경우 cmd를 return
	1. path의 value를 ':' 단위로 split
	2. stat()함수로 해당 경로에 cmd가 존재하는지를 판단
		- /로 끝나는 경로가 있기도 하고, /로 끝나지 않는 경로가 있기도 함
			-> 결과적으로 return되는 cmd_path를 실행하는데에는 영향이 없다.
	3. 동적할당한 메모리는 free
*/

char *get_cmd_path(char *cmd)
{
	char		*path_value;
	char		**paths;
	char		*_cmd;
	char		*cmd_path;
	int			i;
	struct stat	st;

	if (stat(cmd, &st) == 0)
		return (cmd);
	path_value = get_env(g_info.envp, "PATH");
	paths = ft_split(path_value, ':');
#ifdef TEST11
	i = -1;
	while (paths[++i])
		printf("%s\n", paths[i]);
#endif
	_cmd = ft_strdup("/");				// /
	_cmd = ft_strjoin(_cmd, cmd);		// /cmd
	cmd_path = NULL;
	i = -1;
	while (paths[++i])
	{
		cmd_path = ft_strdup(paths[i]);
		cmd_path = ft_strjoin(cmd_path, _cmd);
		if (stat(cmd_path, &st) == 0)
			break;
		free(cmd_path);
		cmd_path = NULL;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	free(_cmd);
	if (cmd_path)
		return (cmd_path);
	else
		return (NULL);
}

/*

	exec_cmd_child 기능

	- pipe가 있는 경우에도 사용되기 때문에 함수화하였음

	1. builtin이라면 builtin 실행
	2. 그 외 cmd들은 환경 변수 PATH 경로에서 실행 파일을 찾아 실행

*/

void exec_cmd_child(t_cmd *cmd)
{
	char	*cmd_path;

	if (is_builtin(cmd->argv[0]))
		exec_builtin(cmd);
	else
	{
		cmd_path = get_cmd_path(cmd->argv[0]);
#ifdef TEST11
		printf("cmd_path : %s\n", cmd_path);
#endif
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
	exec_cmd 기능

	- pipe나 redirection 없이 일반적으로 cmd를 실행하기 위한 함수
	- 기본적으로 subshell에서 cmd가 실행되기 때문에 fork() 사용
	- exit()의 경우 subshell에서 실행되는 것이 아니기 때문에 따로 예외를 만듦
		- 참고로 exit()가 pipe 와 같이 사용되는 경우 동작이 다름
*/

void exec_cmd(t_cmd *cmd)
{
	pid_t	pid;

	if (!ft_strcmp(cmd->argv[0], "exit"))
		ft_exit();
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
		}
		waitpid(pid, NULL, 0);
	}
}
