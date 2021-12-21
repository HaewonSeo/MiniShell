#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>//

typedef struct            s_cmd
{
    int                    argc;
    char                 **argv;                // main의 argv 처럼 cmd를 공백 기준으로 분리
    int                    pipe;                // pipe가 있으면 1
    int                    redirection;        // redirection이 있으면 1
    int                    quote;
    struct s_cmd        *next;                // 추가했어요!
}                        t_cmd;

typedef struct			s_info
{
	//t_term				term;				// terminal 관련 속성
	//char				**argv;
	//char				**envp;				// subshell에게 envp를 전달하기 위한 포인터
	//t_env				*head_env;			// 환경변수 연결 리스트의 head
	t_cmd				*head_cmd;			// cmd 연결 리스트의 head
	//t_env				*head_shell_var;	// 쉘 변수 연결 리스트의 head
	//int					exit_status;		// 종료 상태
}						t_info;

t_info					g_info;

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

void	ft_bzero(void *b, size_t len)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = b;
	while (i < len)
		str[i++] = 0;
}

void	*ft_calloc(size_t number, size_t size)
{
	void	*mem;

	mem = malloc(number * size);
	if (!mem)
		return (NULL);
	ft_bzero(mem, (number * size));
	return (mem);
}


int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
/*
*******************************************************************
*/


/*
** init && free
*/

void    init_cmd(char *str, t_cmd *tmp)
{
    int     i;
    int     j;

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
    tmp->quote = 0;
    tmp->next = NULL;
}

void    free_cmd(t_cmd *tmp) //env의 free와 같은 형식
{
    t_cmd   *del;
    int     i;

    i = 0;
    while (tmp)
    {
        del = tmp;
        tmp = tmp->next;
        free(del->argv[0]);
        while (del->argv[i])
        {
            free(del->argv[i]);
            i++;
        }
        free(del);
    }
    free(tmp);
}

void   new_init(char *str, t_cmd *tmp)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < ft_strlen(str))
    {
        while (str[i] && str[i] == ' ')
            i++;
        if (str[i] == '\'')
        {
            i++;
            while (str[i] && str[i] != '\'')
                i++;
            i++;
            j++;
            continue ;
        }
        else if (str[i] == '\"')
        {
            i++;
            while (str[i] && str[i] != '\"')
                i++;
            i++;
            j++;
            continue ;
        }
        while (str[i] && str[i] != ' ')
            i++;
        j++;
        i++;
    }
    tmp->argv = (char **)malloc(sizeof(char *) * (j + 1));
}

/*
** pipe && redirection
*/

int check_pipe(t_cmd *tmp)
{
    int i;

    i = 1;
    while (tmp->argv[i])
    {
        if (tmp->argv[i][0] == '|')
            return (1);
        else
            i++;
    }
    return (0);
}

int check_redi(t_cmd *tmp)// <은1 <<는2 >는3 >>는4
{
    int i;

    i = 1;
    while (tmp->argv[i])
    {
        if (tmp->argv[i][0] == '<')
        {
            if (!tmp->argv[i][1])
                return (1);
            else if (tmp->argv[i][1] == '<')
                return (2);
        }
        else if (tmp->argv[i][0] == '>')
        {
            if (!tmp->argv[i][1])
                return (3);
            else if (tmp->argv[i][1] == '>')
                return (4);
        }
        i++;
    }
    return (0);
}

/*
** check
*/

int check_cmd(t_cmd *tmp)
{
    int i;
    int j;
    int k;

    i = 0;
    j = 0;
    k = 0;
    while (tmp->argv[j])
        j++;
    while (i < j)
    {
        if (!ft_strcmp(tmp->argv[i], "cd") || !ft_strcmp(tmp->argv[i], "echo")
	    || !ft_strcmp(tmp->argv[i], "pwd") || !ft_strcmp(tmp->argv[i], "env")
	    || !ft_strcmp(tmp->argv[i], "export") || !ft_strcmp(tmp->argv[i], "export")
	    || !ft_strcmp(tmp->argv[i], "unset") || !ft_strcmp(tmp->argv[i], "exit"))
            k++;
        if (tmp->pipe == 0)
            break ;
        else
        {
            while (ft_strcmp(tmp->argv[i], "-"))
                i++;
        }
    }
	return (k);
}

int where_pire(char *str)
{
    int i;
    
    i = 0;
    while (str[i])
    {
        if (str[i] == '|')
            return (i + 1);
        else if (str[i] == '>')
        {
            if (str[i + 1] == '>')
                return (i + 2);
            else if (str[i + 1] == ' ')
                return (i + 1);
        }
        else if (str[i] == '<')
        {
            if (str[i + 1] == '<')
                return (i + 2);
            else if (str[i + 1] == ' ')
                return (i + 1);
        }
        i++;
    }
    return (-1);
}

int where_quote(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\'')
            return (i);
        if (str[i] == '\"')
            return (i);
        i++;
    }
    return (-1);
}

int check_quote(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\'')
            return (1);
        else if (str[i] == '\"')
            return (2);
        i++;
    }
    return (0);
}

/*
** 시작
*/

int parsing_cmd_qu(char *str, t_cmd *tmp)
{
    int i;
    int j;
    int mid;

    i = 0;
    j = 0;
    new_init(str, tmp);
    while (i < ft_strlen(str))
    {
        while (str[i] && str[i] == ' ')
            i++;
        mid = i;
        if (str[i] == '\'')
        {
            i++;
            while (str[i] && str[i] != '\'')
                i++;
            tmp->argv[j] = ft_substr(str, mid + 1, i - mid - 1);
            i++;
            j++;
            continue ;
        }
        else if (str[i] == '\"')
        {
            i++;
            while (str[i] && str[i] != '\"')
                i++;
            tmp->argv[j] = ft_substr(str, mid + 1, i - mid - 1);
            i++;
            j++;
            continue ;
        }
        while (str[i] && str[i] != ' ')
            i++;
        tmp->argv[j] = ft_substr(str, mid, i - mid);
        j++;
        i++;
    }
    tmp->argv[j] = 0;
    return (j);
}



void    re_parsing_cmd(t_cmd *tmp, char *str)
{
    int     i;
    int     j;
    int     k;
    t_cmd   *new;

    i = 0;
    j = 0;
    new = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
    new->quote = check_quote(str);
    while (tmp->argv[i])
    {
        if (tmp->argv[i][0] == '|')
            break ;
        else if (tmp->argv[i][0] == '>')
        {
            if (tmp->argv[i][1] == '>' || !tmp->argv[i][1])
                break ;
        }
        else if (tmp->argv[i][0] == '<')
        {
            if (tmp->argv[i][1] == '<' || !tmp->argv[i][1])
                break ;
        }
        i++;
    }
    k = i + 1;
    new->argv = (char **)malloc(sizeof(char *) * (tmp->argc - k));
    new->argc = tmp->argc - k;
    tmp->argc = tmp->argc - new->argc - 1;
    while (tmp->argv[k])
        new->argv[j++] = tmp->argv[k++];
    new->argv[j] = 0;
    tmp->argv[i] = 0;
    new->pipe = check_pipe(new);
    new->redirection = check_redi(new);
    tmp->next = new;
    new->next = NULL;
    if (where_quote(str) > where_pire(str))
        tmp->quote = 0;
    if (new->pipe > 0 || new->redirection > 0)
        re_parsing_cmd(new, str + where_pire(str));
}

void    parsing_cmd(char *str, t_cmd **cur)
{
    int     i;
    int     j;
    int     mid;
    t_cmd   *tmp;

    i = 0;
    j = 0;
    tmp = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
    init_cmd(str, tmp);
    tmp->quote = check_quote(str);
    while(tmp->quote == 0 && i < ft_strlen(str))
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
    tmp->argv[j] = 0;
    if (tmp->quote != 0)
        j = parsing_cmd_qu(str, tmp);
    tmp->argc = j;
    tmp->pipe = check_pipe(tmp);
    tmp->redirection = check_redi(tmp);
    (*cur)->next = tmp;
    if (where_quote(str) > where_pire(str))
        tmp->quote = 0;
    if (tmp->pipe > 0 || tmp->redirection > 0)
        re_parsing_cmd(tmp, str);
    return ;
}

int main()
{
    char *str = " haai > world   world < ho > a >  j";
    //char *str = " hi | world   world  >  ho j ";
    t_cmd *tmp;
    int i;


    g_info.head_cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd)); 
    tmp = g_info.head_cmd;



    i = 0;
    parsing_cmd(str, &tmp);
    while (tmp->next->argv[i])
    {
       printf("%s\n", tmp->next->argv[i]);
        i++;
    }
    printf("%d\n", tmp->next->quote);
    i = 0;
    printf("-----\n");
    while (tmp->next->next->argv[i])
    {
        printf("%s\n", tmp->next->next->argv[i]);
        i++;
    }
    printf("%d\n", tmp->next->next->quote);
    i = 0;
    printf("-----\n");
    while (tmp->next->next->next->argv[i])
    {
        printf("%s\n", tmp->next->next->next->argv[i]);
        i++;
    }
    printf("%d\n", tmp->next->next->next->quote);
    i = 0;
    printf("-----\n");
    while (tmp->next->next->next->next->argv[i])
    {
        printf("%s\n", tmp->next->next->next->next->argv[i]);
        i++;
    }
    printf("%d\n", tmp->next->next->next->next->quote);
    printf("%d\n", tmp->next->argc);
}