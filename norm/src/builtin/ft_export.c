/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 18:44:06 by haseo             #+#    #+#             */
/*   Updated: 2022/01/04 01:52:19 by haseo            ###   ########.fr       */
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

static void	add_shell_to_envp(char **envp, char *key)
{
	char	*shell_value;
	char	*new;

	if (get_env(envp, key))
		return ;
	shell_value = get_shell(&g_info, key);
	if (shell_value)
	{
		new = ft_strdup(key);
		new = ft_strjoin(new, "=");
		new = ft_strjoin(new, shell_value);
		add_env_new(envp, new);
		free(new);
	}
	else
		add_env_new(envp, key);
	del_shell2(g_info.shell, key);
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
			else if (ft_strchr(cmd->argv[i], '=') != NULL)
				add_env(g_info.envp, cmd->argv[i]);
			else
				add_shell_to_envp(g_info.envp, cmd->argv[i]);
		}
	}
}
