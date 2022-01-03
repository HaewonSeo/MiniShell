/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 22:13:24 by haseo             #+#    #+#             */
/*   Updated: 2022/01/03 22:30:27 by haseo            ###   ########.fr       */
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
	new_shell = (char **)malloc(sizeof(char *) * (i + 1));
	j = -1;
	while (++j < i)
		new_shell[j] = shell[j];
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
		mod_shell(g_info.shell, key, new_value);
	else
		add_shell_new(g_info.shell, str);
	free(key);
}
