# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/12 01:37:10 by haseo             #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2021/12/07 12:10:28 by haseo            ###   ########.fr        #
=======
#    Updated: 2021/12/03 17:40:37 by haseo            ###   ########.fr        #
>>>>>>> b1767cb210a4cc995bb650557675c421bc99e489
#                                                                              #
# **************************************************************************** #

NAME			= minishell

# ----------------------------------
# Compile flag
# ----------------------------------

CC				= gcc
# CFLAGS 			= -Wall -Wextra -Werror
# CFLAGS			+= -g3 -fsanitize=address
CFLAGS			+= -g
USER			= haseo
# USER			= hyejung

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
<<<<<<< HEAD
					./builtin
=======
>>>>>>> b1767cb210a4cc995bb650557675c421bc99e489

vpath %.c $(VPATH_DIR)

# ----------------------------------
# Source & Object file
# ----------------------------------

SRCS			=	minishell.c \
					prompt.c \
					util.c


OBJS			= $(addprefix $(OBJ_DIR)/, ${SRCS:.c=.o})

# ----------------------------------
# Library
# ----------------------------------

LIBFT			= $(LIBFT_DIR)/libft.a
LDFLAGS			= -lft
LDFLAGS			+= -lreadline -L/Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include
# ----------------------------------
# Rules
# ----------------------------------

all:			$(NAME)

$(OBJ_DIR):
					@$(MKDIR) $@
					@$(ECHO) "$(GREEN)[Success]\t $(ORANGE)Create $(OBJ_DIR)$(NOCOLOR)"

$(OBJ_DIR)/%.o: %.c
					@$(CC) -c $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR)/inc -o $@ $^
					@$(ECHO) "$(GREEN)[Success]\t $(ORANGE)Create $@$(NOCOLOR)"

$(LIBFT):
					@$(MAKE) -C $(LIBFT_DIR)

$(NAME):		$(LIBFT) $(OBJ_DIR) ${OBJS}
					@$(CC) $(CFLAGS) -o $@ ${OBJS} -L$(LIBFT_DIR) $(LDFLAGS)
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
