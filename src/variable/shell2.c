/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 22:13:24 by haseo             #+#    #+#             */
/*   Updated: 2022/01/04 12:29:05 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_shell_new(char **shell, char *new)
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
	new_shell = (char **)malloc(sizeof(char *) * (i + 2));
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

void	add_shell(char **shell, char *str)
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
	old_value = get_shell(&g_info, key);
	if (old_value)
	{
		printf("mod\n");
		mod_shell(shell, key, new_value);
	}
	else
	{
		printf("add_new\n");
		add_shell_new(shell, str);
	}
	free(key);
}

void	del_shell2(char **shell, char *key)
{
	int		i;
	char	*del;

	if (shell == NULL)
		return ;
	i = 0;
	del = NULL;
	while (shell[i])
	{
		if (!ft_strncmp(shell[i], key, ft_strlen(key)))
		{
			del = shell[i];
			break ;
		}
		i++;
	}
	while (shell[i])
	{
		shell[i] = shell[i + 1];
		i++;
	}
	if (del)
		free(del);
}
