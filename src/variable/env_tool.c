/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyejung <hyejung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 21:55:20 by hyejung           #+#    #+#             */
/*   Updated: 2022/01/03 21:55:22 by hyejung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_envp(char **envp)
{
	int i;

	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
}

char    *get_env(char **envp, char *key)
{
	int i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0)
			return (envp[i] + ft_strlen(key) + 1);
	}
	return (NULL);
}

void    mod_env(char **envp, char *key, char *value)
{
	int     i;
	char    *new;

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

char    *shell_to_envp(t_info *info, char *tmp, char *str)
{
	del_shell(info, tmp);
	if (ft_strchr(tmp, '=') == NULL)
		str = ft_strjoin(tmp, get_shell(info, tmp));
	return (str);
}
