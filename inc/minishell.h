/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:30:10 by haseo             #+#    #+#             */
/*   Updated: 2021/12/30 21:13:49 by haseo            ###   ########.fr       */
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

#define ETX	3		// ctrl + c : End of Text
#define EOT	4		// ctrl + d : End of Transmission
#define LF	10		// \n : Line feed
#define FS	28		// ctrl + \ : File Separator
#define DEL	127
#define LEFT_ARROW	4479771
#define RIGHT_ARROW	4414235
#define TEST 1

typedef struct			s_term
{
	struct termios		canonical;
	struct termios		noncanonical;
	char				*cm;			// Screen-relative cursor motion.
	char				*ce;			// Clear to end of line.
}						t_term;

/*
cmd도 env처럼 연결리스트로 구현한다면

head_cmd - cmd1    -      cmd2        - cmd3 - ...
          "ls -l >>"  -  "test.txt"   - NULL

이런식으로 구현해보는게 어떨까 생각했습니다.
그래서 순차적으로 명령어를 실행시키는 흐름으로...

*/

typedef struct			s_redir
{
	char 				*l;				// <
	char				*ll;
	char				*r;				// >
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
	int					shell_var;			// 쉘변수이면 1
	t_redir				*redir;				// redirection이 있는 경우 redireciton 관련 정보를 저장
	struct s_cmd		*next;

}						t_cmd;

typedef struct			s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct			s_info
{
	t_term				term;				// terminal 관련 속성
	char				**argv;
	char				**envp;				// subshell에게 envp를 전달하기 위한 포인터
	char				**shell;
	t_env				*head_env;			// 환경변수 연결 리스트의 head
	t_cmd				*head_cmd;			// cmd 연결 리스트의 head
	t_env				*head_shell_var;	// 쉘 변수 연결 리스트의 head
	int					exit_status;		// 종료 상태
}						t_info;

t_info					g_info;				// 전역변수 - 모든 함수에서 접근 가능


/*
** terminal
*/

void	get_canonical_mode();
void	set_noncanonical_mode();
void	set_canonical_mode();

/*
** prompt
*/

char	*prompt();
void	*prompt2();
void	prompt3();
char	*prompt4();

void	get_cursor_pos(int *col, int *row);
void	put_backspace(int *col, int *row);
void	move_cursor_left(int *col, int *row);
void	move_cursor_right(int *col, int *row);
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
** utility
*/

void	ft_perror(const char *str, int errnum);
void	ft_perror1();
void	ft_perror2();
void	ft_perror3(const char *cmd, const char *msg, int errnum);

/*
** cmd
*/

void	init_cmd(char *str, t_cmd *tmp);
void	new_init(char *str, t_cmd *tmp);
void	put_redirection(t_cmd *tmp);
void    parsing_cmd(char *str, t_cmd **tmp);
int		parsing_cmd_qu(char *str, t_cmd *tmp);
void    re_parsing_cmd(t_cmd *tmp, char *str);
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
void    printf_error(int i);
void    ch_right_redi_2(char *str, int i);
void    ch_right_redi(char *str);
void    ch_right_pipe(char *str);
void    ch_right_quote(char *str);
void    check_right(char *str);
int		check_cmd_env(char *str);
t_cmd   *parsing_cmd_env(char *str);

/*
** cmd tool
*/

int		check_i(char *str, t_cmd *tmp, int i, int j, int mid);
int		argv_pipe(t_cmd *tmp);
void	tmp_and_new(t_cmd *tmp, t_cmd *new, char *str);
int		return_j(t_cmd *tmp, char *str);

/*
** shell_env
*/

void    add_shell_env(char *str);
void    add_new_shell_env(char *str, t_info *info);
void    free_shell(char **shel);
char	*get_shell(t_info *info, char *key);
void    del_shell(t_info *info, char *key);


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
** env
*/

void	free_envp(char **env);
void	add_envp_new(t_info *info, char *str);
void	add_envp(t_info *info, char *str);
void	del_envp(t_info *info, char *key);
void	split_envp(char **envp, t_info *info);
void	print_envp(char **envp);
char	*get_env(char **envp, char *key);

#endif
