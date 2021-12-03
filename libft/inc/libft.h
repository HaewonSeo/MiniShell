/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 03:17:02 by haseo             #+#    #+#             */
/*   Updated: 2021/10/10 01:00:41 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

/*
** Part 1
** Memory Functions
*/

void				*ft_memset(void *dest, int c, size_t len);
void				ft_bzero(void *b, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t len);
void				*ft_memccpy(void *dst, const void *src, int c, size_t len);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *b, int c, size_t len);
int					ft_memcmp(const void *b1, const void *b2, size_t len);

/*
** String Functions
*/

size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *big, const char *little, \
															size_t len);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

/*
** Utility Functions
*/

int					ft_atoi(const char *nptr);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);

/*
** Use malloc()
*/

void				*ft_calloc(size_t number, size_t size);
char				*ft_strdup(const char *str);

/*
** Part 2
** String Functions
*/

char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/*
** Print Functions
*/

void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(const char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr(const char *s);

/*
** Bonus part
*/

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(char *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *), \
														void (*del)(void *));

/*
** ft_printf
*/

char				*ft_itoabase(long n, char type);

/*
** gnl
*/

char				*ft_strjoin(char *s1, const char *s2);
int					get_next_line(int fd, char **line);

/*
** cub3D
*/

void				ft_exit(const char *str);
int					ft_isformat(char *str, char *fmt);
void				ft_free2d(char **arr);
int					ft_isdigit_str(const char *str);
size_t				ft_lstmaxwidth(t_list *lst);
size_t				ft_cntword(char const *s, char c);

/*
** push_swap
*/

int					ft_strcmp(const char *s1, const char *s2);

#endif
