#include <stdio.h>
#include <stdlib.h>

typedef struct			s_info
{
	//t_term				term;				// terminal 관련 속성
	//char				**argv;
	char				**envp;				// subshell에게 envp를 전달하기 위한 포인터
	//t_env				*head_env;			// 환경변수 연결 리스트의 head
	//t_cmd				*head_cmd;			// cmd 연결 리스트의 head
	//t_env				*head_shell_var;	// 쉘 변수 연결 리스트의 head
	//int					exit_status;		// 종료 상태
}						t_info;

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (*str != '\0')
	{
		i++;
		str++;
	}
	return (i);
}

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;
	int		k;

	i = 0;
	k = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && str1[k] && str2[k])
	{
		if ((unsigned char)str1[k] == (unsigned char)str2[k])
		{
			i++;
			k++;
		}
		else
			break ;
	}
	return ((unsigned char)str1[k] - (unsigned char)str2[k]);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;

	if (!s)
		return (0);
	new = (char*)malloc(len + 1);
	if (new == NULL)
		return (0);
	i = 0;
	while (i < len && *(s + start + i) && !(start > ft_strlen(s)))
	{
		*(new + i) = *(s + start + i);
		i++;
	}
	*(new + i) = '\0';
	return (new);
}

/*
** 시작
*/

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

int main(int argc, char **argv, char **envp)
{
    t_info info;
    int i;

    split_envp(envp, &info);
    add_envp(&info, "hello=hi");
    del_envp(&info, "USER=hyejung");
    i = 0;
    while (info.envp[i])
    {
        printf("%s\n", info.envp[i]);
        i++;
    }
}