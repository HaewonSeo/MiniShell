
#include "minishell.h"

int check_cmd(char *str)//echo, cd, pwd, export, unset, env, exit
{
    if (!ft_strncmp(str, "echo", 4))
        return (1);//이 경우만 옵션이 있어서 따로 체크했습니다
    else if (!ft_strncmp(str, "cd", 2))
        return (2);
    else if (!ft_strncmp(str, "pwd", 3))
        return (2);
    else if (!ft_strncmp(str, "export", 6))
        return (2);
    else if (!ft_strncmp(str, "unset", 5))
        return (2);
    else if (!ft_strncmp(str, "env", 3))
        return (2);
    else if (!ft_strncmp(str, "exit", 4))
        return (2);
    else
        return (-1);
}//주어진 조건에 명령어들을 체크하는 것인데 더 좋은 방법ㅇㅣ  있을 수 도 모르겠어요ㅜㅜㅠㅜ

void    parsing_cmd(char *str, t_cmd *tmp) //구조체를 새로 만들었습니다
{
    int i;

    i = 0;
    while (str[i] != ' ')
        i++;
    tmp->argv[0] = ft_substr(str, 0, i);
    if (check_cmd(tmp->argv[0]) < 0)//이상한 명령이 들어온 경우 (조건에 없는 명령어등)
    {
        free(tmp->argv[0]);
        return ;
    }
    i++;
    if (str[i] == '-' && check_cmd(tmp->argv[0]) == 1)//옵션이 있는 경우
    {
        tmp->argv[1] = str[i + 1];
        i = i + 2;// 띄어쓰기 위치로 이동
        tmp->argv[2] = ft_substr(str, i + 1, ft_strlen(str) - i + 1);
    }
    else
        tmp->argv[1] = ft_substr(str, i + 1, ft_strlen(str) - i + 1); //뒤에 내용이 더 있는 경우 저장
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