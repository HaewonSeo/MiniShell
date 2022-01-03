/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 11:48:49 by haseo             #+#    #+#             */
/*   Updated: 2022/01/03 17:30:29 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_envp(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	add_envp_new(t_info *info, char *str)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	while (g_info.envp[i])
		i++;
	tmp = (char **)malloc(sizeof(char *) * (i + 2));
	while (j < i)
	{
		tmp[j] = ft_substr(info->envp[j], 0, ft_strlen(info->envp[j]));
		j++;
	}
	tmp[j] = ft_substr(str, 0, ft_strlen(str));
	free_envp(info->envp);
	info->envp = (char **)malloc(sizeof(char *) * (i + 2));
	j = 0;
	while (j < i + 1)
	{
		info->envp[j] = ft_substr(tmp[j], 0, ft_strlen(tmp[j]));
		j++;
	}
	free_envp(tmp);
	info->envp[j] = 0;
}

void    add_envp(t_info *info, char *str)
{
	int     i;
	int     j;
	char    *tmp;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	if (i == 0)
		i++;
	tmp = ft_substr(str, 0, i);
	if (get_shell(info, tmp) != NULL)
	{
		del_shell(info, tmp);
		if (ft_strchr(tmp, '=') == NULL)
			str = ft_strjoin(tmp, get_shell(info, tmp));
	}
	if (get_env(info->envp, tmp))
	{
		while (ft_strncmp(info->envp[j], tmp, i) != 0)
			j++;
		free(info->envp[j]);
		info->envp[j] = ft_substr(str, 0, ft_strlen(str));
	}
	else
		add_envp_new(info, str);
	free(tmp);
}

void    del_envp(t_info *info, char *key)
{
	int i;

	if (!get_env(info->envp, key))
		return ;
	i = 0;
	while (ft_strncmp(info->envp[i], key, ft_strlen(key)))
		i++;
	while (info->envp[i] && info->envp[i + 1])
	{
		info->envp[i] = info->envp[i + 1];
		i++;
	}
	free(info->envp[i]);
	info->envp[i] = 0;
}

void    split_envp(char **envp, t_info *info)
{
	int i;

	i = 0;
	while (envp[i])
		i++;
	info->envp = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		info->envp[i] = ft_substr(envp[i], 0, ft_strlen(envp[i]));
		i++;
	}
	info->envp[i] = 0;
}

void print_envp(char **envp)
{
	int		i;

	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
}

char *get_env(char **envp, char *key)
{
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0)
			return (envp[i] + ft_strlen(key) + 1);
	}
	return (NULL);
}

void	mod_env(char **envp, char *key, char *value)
{
	int		i;
	char	*new;

	new = ft_strdup(key);
	new = ft_strjoin(new, value);
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0)
		{
			free(envp[i]);
			envp[i] = new;
			break ;
		}
	}
}
