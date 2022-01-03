/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 22:32:46 by hyejung           #+#    #+#             */
/*   Updated: 2022/01/04 01:34:04 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_shell(char **shell)
{
	int	i;

	i = 0;
	if (!shell)
		return ;
	while (shell[i])
	{
		printf("%s\n", shell[i]);
		i++;
	}
}

void	mod_shell(char **shell, char *key, char *value)
{
	int		i;
	char	*new;
	char 	*del;

	new = ft_strdup(key);
	new = ft_strjoin(new, value);
	i = -1;
	while (shell[++i])
	{
		if (ft_strncmp(shell[i], key, ft_strlen(key)) == 0)
		{
			del = shell[i];
			shell[i] = new;
			free(del);
			break ;
		}
	}
}
