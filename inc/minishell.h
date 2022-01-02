/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:30:10 by haseo             #+#    #+#             */
/*   Updated: 2022/01/02 21:16:05 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define WSL

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <term.h>
# include <termcap.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"
# include "color.h"
#ifndef WSL
# include <readline/readline.h>
# include <readline/history.h>
#endif

#define ETX	3
#define EOT	4
#define LF	10
#define FS	28
#define DEL	127
#define LEFT_ARROW	4479771
#define RIGHT_ARROW	4414235
#define TEST 1

typedef struct			s_term
{
	struct termios		canonical;
	struct termios		noncanonical;
	char				*cm;
	char				*ce;
}						t_term;

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
	char 				**argv;
	int					pipe;
	int					redirection;
	int					quote;
	int					fd[2];
	int					pipe_prev;
	int					shell_var;
	t_redir				*redir;
	struct s_cmd		*next;

}						t_cmd;

typedef struct			s_info
{
	t_term				term;
	int					argc;
	char				**argv;
	char				**envp;
	char				**shell;
	t_cmd				*head_cmd;
	int					exit_status;
	int					signal;
}						t_info;

t_info					g_info;

/*
** builtin
*/
void	ft_cd(t_cmd *cmd);
void	ft_echo(t_cmd *cmd);
void	ft_env(t_cmd *cmd);
void	ft_exit_with_set_mode(int errnum);
void	ft_exit();
void	ft_export(t_cmd *cmd);
void	ft_pwd();
void	ft_unset(t_cmd *cmd);

/*
** execute
*/

void	exec_input();
int		is_builtin(char *cmd);
void	exec_builtin(t_cmd *cmd);
char	*get_cmd_path(char *cmd);
void	exec_cmd_child(t_cmd *cmd);
void	exec_cmd(t_cmd *cmd);
void	exec_pipe(t_cmd *cur);
void	set_redirection(t_cmd *cur);

/*
** cmd
*/

void	init_cmd(char *str, t_cmd *tmp);
void	new_init(char *str, t_cmd *tmp);
void	put_redirection(t_cmd *tmp);
void	parsing_cmd(char *str, t_cmd **tmp);
int		parsing_cmd_qu(char *str, t_cmd *tmp);
void	re_parsing_cmd(t_cmd *tmp, char *str);
int		check_cmd(t_cmd *tmp);
int		check_pipe(t_cmd *tmp);
int		check_redi(char *str);
void	free_cmd(t_cmd *tmp);
void	remove_redi(t_cmd *tmp);
int		check_cmd(t_cmd *tmp);
int		check_quote(char *str);
int		where_pipe(char *str);
int		where_quote(char *str);
int		where_redi(char *str);
void	printf_error(int i);
void	ch_right_redi_2(char *str, int i);
void	ch_right_redi(char *str);
void	ch_right_pipe(char *str);
void	ch_right_quote(char *str);
void	check_right(char *str);
int		check_cmd_env(char *str);
t_cmd   *parsing_cmd_env(char *str);
void	finish_cmd(t_cmd *tmp, char *str);
void    free_argv(char **tmp, int len);
void    re_parsing_cmd_env(t_cmd *tmp);

/*
** cmd tool
*/

int		check_i(char *str, t_cmd *tmp, int i, int j, int mid);
int		argv_pipe(t_cmd *tmp);
void	tmp_and_new(t_cmd *tmp, t_cmd *new, char *str);
int		return_j(t_cmd *tmp, char *str);


/*
** cursor
*/

void	get_cursor_pos(int *col, int *row);
void	put_backspace(int *col, int *row);
void	move_cursor_left(int *col, int *row);
void	move_cursor_right(int *col, int *row);

/*
** prompt
*/

#ifndef WSL
char	*prompt();
#endif
char	*prompt4();

/*
** signal
*/

void	signal_handler(int signum);

/*
** terminal_input_mode
*/

void	get_canonical_mode();
void	set_noncanonical_mode();
void	set_canonical_mode();

/*
** utility
*/

void	ft_perror(const char *str, int errnum);
void	ft_perror1(const char *cmd, const char *msg, int errnum);
void	ft_perror2(const char *cmd, const char *arg, const char *msg, int errnum);
void	ft_perror3(const char *cmd, const char *msg, int errnum);
void	ft_perror4(const char *cmd, int i, const char *msg, int errnum);
void	print_cmd(t_cmd *tmp, char *input);

/*
** env
*/

void	free_envp(char **env);
void	add_envp_new(t_info *info, char *str);
void	add_envp(t_info *info, char *str);
void	del_envp(t_info *info, char *key);
void	split_envp(char **envp, t_info *info);
void	print_envp(char **envp);
char	*get_env(char **envp, char *key);
void	mod_env(char **envp, char *key, char *value);

/*
** shell
*/

void	add_shell_env(char *str);
void	add_new_shell_env(char *str, t_info *info);
void	free_shell(char **shel);
char	*get_shell(t_info *info, char *key);
void	del_shell(t_info *info, char *key);
void	print_shell(char **shell);

#endif
