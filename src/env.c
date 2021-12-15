
#include "minishell.h"

void    add_env(t_env *head, char *t_key, char *t_value)
{
    t_env   *new;
    t_env   *tmp;

    new = (t_env *)malloc(sizeof(t_env));
    new->key = ft_strdup(t_key);
    if (t_value)
        new->value = ft_strdup(t_value);
    else
        new->value = ft_strdup("");
    new->next = NULL;
    tmp = head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    return ;
}

void    split_env(char **envp, t_env *head)
{
    int     i;
    int     j;
    char    *k;
    char    *v;
    t_env *cur;
    t_env *new;

    i = 0;
    cur = head;
    while (envp[i])
    {
        j = 0;
        while (envp[i][j] != '=')
            j++;
        k = ft_substr(envp[i], 0, j);
        v = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - j - 1);
        new = (t_env *)malloc(sizeof(t_env));
        new->key = k;
        new->value = v;
        cur->next = new;
        cur = cur->next;
        i++;
    }
    return ;
}

void    del_env(t_env *head, char *key)
{
    t_env *cur;
    t_env *tmp;

    cur = head;
    while (cur->next)
    {
        if (!ft_strncmp(cur->next->key, key, ft_strlen(key)))
        {
            tmp = cur->next;
            cur->next = tmp->next;
            free(tmp->key);
            free(tmp->value);
            free(tmp);
            break;
        }
        cur = cur->next;
    }
}

void    finish_env(t_env *head)
{
    t_env   *tmp;
    t_env   *del;

    tmp = head;
    while (tmp)
    {
        del = tmp;
        tmp = tmp->next;
        if (del->key)
            free(del->key);
        if (del->value)
            free(del->value);
        free(del);
    }
    free(head);
}

char *get_env(t_env *head, char *key)
{
    t_env *cur;
    t_env *ret;

    cur = head;
    while (cur->next) {
        if (!ft_strncmp(cur->next->key, key, ft_strlen(key)))
        {
            ret = ft_strdup(cur->next->value);
            return (ret);
        }
        cur = cur->next;
    }
    return (NULL);
}

void    print_env(t_env *head)
{
    t_env   *tmp;

    tmp = head;
    while (tmp)
    {
        printf("%s=", tmp->key);
        if (tmp->value)
            printf("%s\n", tmp->value);
        else
            printf("\n");
        tmp = tmp->next;
    }
}
