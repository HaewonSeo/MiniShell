# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/12 01:37:10 by haseo             #+#    #+#              #
#    Updated: 2022/01/04 18:07:50 by haseo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

# ----------------------------------
# Compile flag
# ----------------------------------

CC				= gcc
CFLAGS 			= -Wall -Wextra -Werror

# ----------------------------------
# Command
# ----------------------------------

CP				= cp
RM				= rm -f
MKDIR			= mkdir -p
RMDIR			= rm -rf
ECHO			= echo

# ----------------------------------
# Echo Color
# ----------------------------------

NOCOLOR			= \033[0m
RED				= \033[0;31m
GREEN			= \033[0;32m
ORANGE			= \033[0;33m
BLUE			= \033[0;34m
PURPLE			= \033[0;35m
CYAN			= \033[0;36m
LIGHTGRAY		= \033[0;37m
DARKGRAY		= \033[1;30m
LIGHTRED		= \033[1;31m
LIGHTGREEN		= \033[1;32m
YELLOW			= \033[1;33m
LIGHTBLUE		= \033[1;34m
LIGHTPURPLE		= \033[1;35m
LIGHTCYAN		= \033[1;36m
WHITE			= \033[1;37m

# ----------------------------------
# Directory
# ----------------------------------

INC_DIR			=	./inc
SRC_DIR			=	./src
OBJ_DIR			=	./obj
LIBFT_DIR		=	./libft
VPATH_DIR		=	./src \
					./src/builtin \
					./src/execute \
					./src/parsing \
					./src/prompt \
					./src/utility \
					./src/variable

vpath %.c $(VPATH_DIR)

# ----------------------------------
# Source & Object file
# ----------------------------------

SRCS			=	minishell.c \
					ft_cd.c \
					ft_echo.c \
					ft_env.c \
					ft_exit.c \
					ft_export.c \
					ft_pwd.c \
					ft_unset.c \
					execute_builtin.c \
					execute_cmd.c \
					execute_pipe.c \
					execute.c \
					set_redirection.c \
					cmd_check.c \
					cmd_env.c \
					cmd_infree.c \
					cmd_pire.c \
					cmd_right.c \
					cmd_tool.c \
					cmd.c \
					prompt.c \
					signal.c \
					error.c \
					env_tool.c \
					env.c \
					env2.c \
					shell_tool.c \
					shell.c \
					shell2.c

OBJS			= $(addprefix $(OBJ_DIR)/, ${SRCS:.c=.o})

# ----------------------------------
# Library
# ----------------------------------

LIBFT			= $(LIBFT_DIR)/libft.a
LDFLAGS			= -lft
# ifeq ($(OS), Darwin)
LDFLAGS		+= -lreadline -L /Users/$(USER)/.brew/opt/readline/lib
# else
	# LDFLAGS		+= -lncurses
# endif

# ----------------------------------
# Rules
# ----------------------------------

all:			$(NAME)

$(OBJ_DIR):
					@$(MKDIR) $@
					@$(ECHO) "$(GREEN)[Success]\t $(ORANGE)Create $(OBJ_DIR)$(NOCOLOR)"

$(OBJ_DIR)/%.o: %.c
					@$(CC) -c $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR)/inc -I /Users/$(USER)/.brew/opt/readline/include -o $@ $^
					@$(ECHO) "$(GREEN)[Success]\t $(ORANGE)Create $@$(NOCOLOR)"

$(LIBFT):
					@$(MAKE) -C $(LIBFT_DIR)

$(NAME):		$(LIBFT) $(OBJ_DIR) ${OBJS}
					@$(CC) $(CFLAGS) -o $@ ${OBJS} -L $(LIBFT_DIR) $(LDFLAGS)
					@$(ECHO) "$(GREEN)[Success]\t $(BLUE)Create $@ \t$(NOCOLOR)"

clean:
					@$(MAKE) -C $(LIBFT_DIR) clean
					@$(RM) $(OBJS)
					@$(RMDIR) $(OBJ_DIR)
					@$(ECHO) "$(GREEN)[Success]\t $(RED)Remove $(OBJ_DIR)$(NOCOLOR)"

fclean:			clean
					@$(MAKE) -C $(LIBFT_DIR) fclean
					@$(RM) $(NAME)
					@$(ECHO) "$(GREEN)[Success]\t $(RED)Remove $(NAME)$(NOCOLOR)"

re:				fclean all
