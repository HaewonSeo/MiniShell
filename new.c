#include <stdio.h>
#include <stdlib.h>

typedef struct            s_cmd
{
    int                    argc;
    char                 **argv;                // main의 argv 처럼 cmd를 공백 기준으로 분리
    int                    pipe;                // pipe가 있으면 1
    int                    redirection;        // redirection이 있으면 1
    struct s_cmd        *next;                // 추가했어요!
}                        t_cmd;

int ft_strlen(const char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
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

void    init_cmd(char *str, t_cmd *tmp)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (str[i])
    {
        while (str[i] && str[i] == ' ')
            i++;
        j++;
        i++;
    }
    tmp->argc = 0;
    tmp->argv = (char **)malloc(sizeof(char *) * (j + 1));
    tmp->pipe = 0;
    tmp->redirection = 0;
    tmp->next = NULL;
}

void check_cmd(char *str, t_cmd *tmp)
{
    int i;
    int j;
    int mid;

    i = 0;
    j = 0;
    init_cmd(str, tmp);
    while(i < ft_strlen(str))
    {
        while (str[i] && str[i] == ' ')
            i++;
        mid = i;
        while (str[i] && str[i] != ' ')
            i++;
        tmp->argv[j] = ft_substr(str, mid, i - mid);
        j++;
        i++;
    }
	tmp->argv[j] = NULL;
}

int main()
{
    char *str = "  hi  world   world ho    j";
    t_cmd tmp;
    int i;

    i = 0;
    check_cmd(str, &tmp);
    while (tmp.argv[i])
    {
        printf("%s\n", tmp.argv[i]);
        i++;
    }
}