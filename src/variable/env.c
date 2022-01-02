/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 11:48:49 by haseo             #+#    #+#             */
/*   Updated: 2022/01/01 23:19:08 by haseo            ###   ########.fr       */
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

void    add_envp_new(t_info *info, char *str)
{
	int i;
	int j;
	char **tmp;

	i = 0;
	j = 0;
	while (info->envp[i])
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
	tmp = ft_substr(str, 0, i);
	if (get_shell(info, tmp))//
		del_shell(info, tmp);//
	if (!getenv(tmp))
		add_envp_new(info, str);
	else
	{
		while (ft_strncmp(info->envp[j], tmp, i))
			j++;
		free(info->envp[j]);
		info->envp[j] = ft_substr(str, 0, ft_strlen(str));
	}
}

void    del_envp(t_info *info, char *key)
{
	int i;

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

void    split_envp(char **envp, t_info *info)//g_info.envp가 들어올 거(뒤)
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
	char	*new_env;

	new_env = ft_strdup(key);
	new_env = ft_strjoin(new_env, "=");
	new_env = ft_strjoin(new_env, value);
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0)
		{
			free(envp[i]);
			envp[i] = new_env;
			break ;
		}
	}
}
