/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 18:43:46 by haseo             #+#    #+#             */
/*   Updated: 2022/01/01 23:23:28 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_home()
{
	char	*path;

	path = get_env(g_info.envp, "HOME");
	if (!path || chdir(path) == -1)
		ft_perror1("cd", "No $HOME", (int)EPERM);
	else
	{
		mod_env(g_info.envp, "PWD", getcwd(NULL, 0));
		g_info.exit_status = 0;
	}
}

static void	cd_envv(char *arg)
{
	char	*path;

	path = get_env(g_info.envp, &arg[1]);
	if (!path || chdir(path) == -1)
		ft_perror2("cd", arg, "No such argument", (int)EPERM);
	else
	{
		mod_env(g_info.envp, "PWD", getcwd(NULL, 0));
		g_info.exit_status = 0;
	}
}

static void	cd_path(const char *path)
{
	if (!path || chdir(path) == -1)
		ft_perror2("cd", path, "No such file or directory", (int)EPERM);
	else
	{
		mod_env(g_info.envp, "PWD", getcwd(NULL, 0));
		g_info.exit_status = 0;
	}
}

void		ft_cd(t_cmd *cmd)
{
	if (cmd->argc > 2)
		ft_perror1("cd", "too many arguments", EPERM);
	else if (cmd->argc == 1 || !ft_strcmp(cmd->argv[1], "~"))
		cd_home();
	else if (cmd->argc == 2 && cmd->argv[1][0] == '$')
		cd_envv(cmd->argv[1]);
	else if (cmd->argc == 2 && cmd->argv[1][0] != '~' && cmd->argv[1][0] != '$')
		cd_path(cmd->argv[1]);
	else
		ft_perror2("cd", cmd->argv[1], "No such file or directory", EPERM);
}
