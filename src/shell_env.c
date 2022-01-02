
#include "minishell.h"

void    free_shell(char **shel)
{
	int i;

	i = 0;
	while (shel[i])
	{
		free(shel[i]);
		i++;
	}
	free(shel);
}

void    add_new_shell_env(char *str, t_info *info)
{
    int     i;
    int     j;
    char    **tmp;

    i = 0;
    j = 0;
    while (info->shell[i])
        i++;
    tmp = (char **)malloc(sizeof(char *) * (i + 2));
	while (j < i)
	{
		tmp[j] = ft_substr(info->shell[j], 0, ft_strlen(info->shell[j]));
		j++;
	}
	tmp[j] = ft_substr(str, 0, ft_strlen(str));
	free_shell(info->shell);
	info->shell = (char **)malloc(sizeof(char *) * (i + 2));
	j = 0;
	while (j < i + 1)
	{
		info->shell[j] = ft_substr(tmp[j], 0, ft_strlen(tmp[j]));
		j++;
	}
	free_shell(tmp);
	info->shell[j] = 0;
}

void    add_shell_env(char *str)
{
    int     i;
    char    *tmp;

    i = 0;
    while (str[i])
    {
        if (str[i] == '=')
            break ;
        i++;
    }
    tmp = ft_substr(str, 0, i);
    if (getenv(tmp))
        add_envp(&g_info, str);
    else
        add_new_shell_env(str, &g_info);
}

char *get_shell(t_info *info, char *key)
{
	int		i;

	i = -1;
	while (info->shell[++i])
	{
		if (ft_strncmp(info->shell[i], key, ft_strlen(key)) == 0)
			return (info->shell[i] + ft_strlen(key) + 1);
	}
	return (NULL);
}

void    del_shell(t_info *info, char *key)
{
	int i;

	i = 0;
	while (ft_strncmp(info->shell[i], key, ft_strlen(key)))
		i++;
	while (info->shell[i] && info->shell[i + 1])
	{
		info->shell[i] = info->shell[i + 1];
		i++;
	}
	free(info->shell[i]);
	info->shell[i] = 0;
}

void	print_shell(char **shell)
{
	int		i;

	i = -1;
	while (shell[++i])
		printf("%s\n", shell[i]);
}
