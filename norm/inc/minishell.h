/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:30:10 by haseo             #+#    #+#             */
/*   Updated: 2022/01/07 18:01:16 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include <readline/readline.h>
# include <readline/history.h>

# define ETX				3
# define EOT				4
# define LF					10
# define FS					28
# define DEL				127
# define LEFT_ARROW			4479771
# define RIGHT_ARROW		4414235

typedef struct s_redir
{
	char				*l;
	char				*ll;
	char				*r;
	char				*rr;
}						t_redir;

typedef struct s_cmd
{
	int					argc;
	char				**argv;
	int					pipe;
	int					redirection;
	int					quote;
	int					fd[2];
	int					pipe_prev;
	int					shell_var;
	t_redir				*redir;
	struct s_cmd		*next;

}						t_cmd;

typedef struct s_info
{
	int					argc;
	char				**argv;
	char				**envp;
	char				**shell;
	int					shell_len;
	t_cmd				*head_cmd;
	int					exit_status;
}						t_info;

t_info	g_info;

/*
** builtin
*/

void	echo_val(char *arg);
void	echo_env(char *arg);
void	ft_cd(t_cmd *cmd);
void	ft_echo(t_cmd *cmd);
void	ft_env(t_cmd *cmd);
void	ft_exit(void);
void	ft_export(t_cmd *cmd);
void	ft_pwd(void);
void	ft_unset(t_cmd *cmd);

/*
** execute
*/

int		is_builtin(char *cmd);
int		is_builtin_on_child(char *cmd);
int		is_builtin_on_parent(char *cmd);
void	exec_input(t_cmd *cmd);
void	exec_builtin(t_cmd *cmd);
char	*get_cmd_path(char *cmd, char **paths);
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
int		check_redi(t_cmd *tmp);
void	free_cmd(t_cmd *tmp);
void	remove_redi(t_cmd *tmp);
int		check_cmd(t_cmd *tmp);
int		check_quote(char *str);
int		where_pipe(char *str);
int		where_quote(char *str);
int		where_redi(char *str);
int		printf_error(int i);
int		ch_right_redi_2(char *str, int i);
int		ch_right_redi(char *str);
int		ch_right_pipe(char *str);
int		ch_right_quote(char *str);
int		check_right(char *str);
int		check_cmd_env(char *str);
t_cmd	*parsing_cmd_env(char *str);
void	finish_cmd(t_cmd *tmp, char *str);
void	free_argv(char **tmp, int len);
void	re_parsing_cmd_env(t_cmd *tmp);
int		check_i(char *str, t_cmd *tmp, int i, int j);

/*
** cmd tool
*/

int		check_i(char *str, t_cmd *tmp, int i, int j);
int		argv_pipe(t_cmd *tmp);
void	tmp_and_new(t_cmd *tmp, t_cmd *new, char *str);
int		return_j(t_cmd *tmp, char *str);

/*
** prompt
*/

char	*prompt(void);
char	*prompt_heredoc(void);

/*
** signal
*/

void	signal_handler(int signum);

/*
** utility
*/

void	ft_perror(char *str, int errnum);
void	ft_perror1(char *cmd, char *msg, int errnum);
void	ft_perror2(char *cmd, char *arg, char *msg, int errnum);
void	ft_perror3(char *cmd, char *msg, int errnum);
void	ft_perror4(char *cmd, int i, char *msg, int errnum);

/*
** env
*/

void	free_envp(char **env);
void	add_envp_new(t_info *info, char *str);
void	add_envp(t_info *info, char *str);
void	del_envp(t_info *info, char *key);
void	del_env2(char **env, char *key);
void	split_envp(char **envp, t_info *info);
void	print_envp(char **envp);
char	*get_env(char **envp, char *key);
void	mod_env(char **envp, char *key, char *value);
char	*shell_to_envp(t_info *info, char *tmp, char *str);
void	add_env_new(char **envp, char *new);
void	add_env(char **envp, char *str);

/*
** shell
*/

void	add_shell_env(char *str);
void	add_new_shell_env(char *str, t_info *info);
void	free_shell(char **shel);
char	*get_shell(t_info *info, char *key);
void	del_shell(t_info *info, char *key);
void	print_shell(char **shell);
void	mod_shell(char **shell, char *key, char *value);
void	add_shell_new(char **shell, char *new);
void	add_shell(char **shell, char *str);
void	del_shell2(char **shell, char *key);

#endif
