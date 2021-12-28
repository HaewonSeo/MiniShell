#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>//

typedef struct			s_redir
{
	char 				*l;
	char				*ll;
	char				*r;
	char				*rr;
}						t_redir;

typedef struct			s_cmd
{
	int					argc;
	char 				**argv;				// main의 argv 처럼 cmd를 공백 기준으로 분리
	int					pipe;				// pipe가 있으면 1
	int					redirection;		// redirection이 있으면 1
	int					quote;				// '는 1 "는 2
	int					fd[2];				// 현재 cmd에 pipe가 존재하는 경우 next_cmd의 fd[]를 생성한다.(pipe() 사용)
	int					pipe_prev;			// 직전 cmd에 pipe가 있으면 1
	t_redir				*redir;				// redirection이 있는 경우 redireciton 관련 정보를 저장
	struct s_cmd		*next;

}		                t_cmd;

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
    tmp->fd[0] = 0;
    tmp->fd[1] = 0;
    tmp->next = NULL;
    tmp->redir = (t_redir *)ft_calloc(1, sizeof(t_redir));///
    //init_t_redi((tmp->redir));//
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
        i = 0;
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

int check_redi(char *str)// <은1 <<는2 >는3 >>는4
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '<')
        {
            if (str[i + 1] == ' ')
                return (1);
            else if (str[i + 1] == '<')
                return (2);
        }
        else if (str[i] == '>')
        {
            if (str[i + 1] == ' ')
                return (3);
            else if (str[i + 1] == '>')
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

int where_redi(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '>')
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

int where_pipe(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '|')
            return (i + 1);
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
* check_right
*/

void    printf_error(int i)
{
    if (i == 1)
    {
        printf("error : quote error\n");
        return ;
    }
    if (i == 2)
    {
        printf("error : parse error near `|'\n");
        return ;
    }
    if (i == 3)
    {
        printf("error : parse error near `\\n'\n");
        return ;
    }
}

void    ch_right_redi_2(char *str, int i)
{
    while (str[i] && str[i] == ' ')
    {
                i++;
            if (str[i] == '|')
                printf_error(3);
            if (str[i] == '>' || str[i] == '<')
                printf_error(3);
            if (!str[i])
                printf_error(3);
    }
}

void    ch_right_redi(char *str)
{
    int i;

    i = 0;
     while (str[i])
    {
        if (str[i] == '>')
        {
            i++;
            if (str[i] == '>')
                i++;
            ch_right_redi_2(str, i);
        }
        if (str[i] == '<')
        {
            i++;
            if (str[i] == '<')
                i++;
            ch_right_redi_2(str, i);
        }
        i++;
    }
}

void    ch_right_pipe(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '|')
        {
            i++;
            while (str[i] && str[i] == ' ')
                i++;
            if (str[i] == '|')
                printf_error(2);
            if (str[i] == '>' || str[i] == '<')
                printf_error(2);
            if (!str[i])
                printf_error(2);
        }
        i++;
    }
}

void    ch_right_quote(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\'')
        {
            i++;
            while (str[i] && str[i] != '\'')
                i++;
            if (i >= ft_strlen(str))
                printf_error(1);
        }
        if (str[i] == '\"')
        {
            i++;
            while (str[i] && str[i] != '\"')
                i++;
            if (i >= ft_strlen(str))
                printf_error(1);
        }
        i++;
    }
}

void    check_right(char *str) // | < << > >> " '
{
    ch_right_quote(str);
    ch_right_pipe(str);
    ch_right_redi(str);
}


/*
** 시작
*/

void    put_redirection(t_cmd *tmp)
{
    int i;

    i = 0;
    if (tmp->redirection == 0)
        return ;
    while (i < tmp->argc)
    {
        if (tmp->argv[i][0] == '<')
        {
            if (!tmp->argv[i][1])
                tmp->redir->l = tmp->argv[i + 1];
            else if (tmp->argv[i][1] == '<')
                tmp->redir->ll = tmp->argv[i + 1];
            i++;
        }
        if (tmp->argv[i][0] == '>')
        {
            if (!tmp->argv[i][1])
                tmp->redir->r = tmp->argv[i + 1];
            else if (tmp->argv[i][1] == '>')
                tmp->redir->rr = tmp->argv[i + 1];
            i++;
        }
        i++;
    }
}

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

void    remove_redi(t_cmd *tmp)
{
    int     i;
    int     j;

    i = 0;
    while (tmp->argv[i])
    {
        if (tmp->argv[i][0] == '<')
        {
            j = i;
            while (tmp->argv[j + 2])
            {
                tmp->argv[j] = tmp->argv[j + 2];
                j++;
            }
            tmp->argv[j] = NULL;
            i = 0;
            continue ;
        }
        if (tmp->argv[i][0] == '>')
        {
            j = i;
            while (tmp->argv[j + 2])
            {
                tmp->argv[j] = tmp->argv[j + 2];
                j++;
            }
            tmp->argv[j] = NULL;
            i = 0;
            continue ;
        }
        i++;
    }
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
    new->redir = (t_redir *)ft_calloc(1, sizeof(t_redir));
    new->quote = check_quote(str);
    while (tmp->argv[i])
    {
        if (tmp->argv[i][0] == '|')
            break ;
        i++;
    }
    k = i + 1;
    new->argv = (char **)malloc(sizeof(char *) * (tmp->argc - k + 1));
    new->argc = tmp->argc - k;
    tmp->argc = tmp->argc - new->argc - 1;
    while (tmp->argv[k])
        new->argv[j++] = tmp->argv[k++];
    new->argv[j] = 0;
    tmp->argv[i] = 0;
    new->pipe = check_pipe(new);
    k = where_pire(str);
    new->redirection = check_redi(str + k);
    tmp->next = new;
    new->next = NULL;
    if (where_quote(str) > where_pire(str))
        tmp->quote = 0;
    if (new->pipe > 0)
        re_parsing_cmd(new, str + k);
    put_redirection(new);
    remove_redi(new);
}

void    parsing_cmd(char *str, t_cmd **cur)
{
    int     i;
    int     j;
    int     mid;
    t_cmd   *tmp;

    i = 0;
    j = 0;
    check_right(str);
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
    tmp->redirection = check_redi(str);
    if (tmp->pipe == 1 && where_pire(str) < where_redi(str))
        tmp->redirection = 0;
    (*cur)->next = tmp;
    if (where_quote(str) > where_pire(str))
        tmp->quote = 0;
    if (tmp->pipe > 0)
        re_parsing_cmd(tmp, str);
    put_redirection(tmp);//
    remove_redi(tmp);//
    return ;
}

/*
*******
*/

int main()
{
   // char *str = " haai << wo > aa | rld > ww";
    char *str = " h <  \" wor < a\"  > b | w > sss >> qqq lw";
    t_cmd *tmp;
    int i;


    g_info.head_cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
    tmp = g_info.head_cmd;



    i = 0;
    printf("---\n");
    parsing_cmd(str, &tmp);
   while (tmp->next->argv[i])
    {
       printf("%s\n", tmp->next->argv[i]);
        i++;
    }
    printf("%s|%s|%s|%s\n", tmp->next->redir->r,tmp->next->redir->rr,tmp->next->redir->l,tmp->next->redir->ll);
    printf("%d\n", tmp->next->quote);
    i = 0;
    printf("-----\n");
    while (tmp->next->next->argv[i] && i < 6)
    {
        printf("%s\n", tmp->next->next->argv[i]);
        i++;
    }
     printf("%s %s %s %s\n", tmp->next->next->redir->r, tmp->next->next->redir->rr,tmp->next->next->redir->l,tmp->next->next->redir->ll);
    printf("%d\n", tmp->next->next->quote);
    /*
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
    printf("%d\n", tmp->next->argc);*/
}
