/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 22:11:36 by haseo             #+#    #+#             */
/*   Updated: 2022/01/04 17:27:50 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env_new(char **envp, char *new)
{
	int		i;
	int		j;
	char	**new_envp;

	i = 0;
	while (envp[i])
		i++;
	new_envp = (char **)malloc(sizeof(char *) * (i + 2));
	j = -1;
	while (++j < i)
		new_envp[j] = envp[j];
	new_envp[j] = ft_strdup(new);
	new_envp[j + 1] = NULL;
	g_info.envp = new_envp;
	free(envp);
}

void	add_env(char **envp, char *str)
{
	char	*key;
	char	*old_value;
	char	*new_value;
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
			break ;
	}
	if (i == 0)
		i++;
	key = ft_substr(str, 0, i);
	new_value = ft_strchr(str, '=');
	old_value = get_env(envp, key);
	if (old_value)
		mod_env(envp, key, new_value);
	else
		add_env_new(envp, str);
	del_shell(&g_info, key);
	free(key);
}

void	del_env2(char **env, char *key)
{
	int		i;
	char	*del;

	if (env == NULL)
		return ;
	i = 0;
	del = NULL;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, ft_strlen(key)))
		{
			del = env[i];
			break ;
		}
		i++;
	}
	while (env[i])
	{
		env[i] = env[i + 1];
		i++;
	}
	if (del)
		free(del);
}
