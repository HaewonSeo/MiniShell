# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/12 01:37:10 by haseo             #+#    #+#              #
#    Updated: 2021/11/30 15:09:52 by haseo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

# ----------------------------------
# Compile flag
# ----------------------------------

CC				= gcc
CFLAGS 			= -Wall -Wextra -Werror
# CFLAGS			+= -g3 -fsanitize=address
# CFLAGS			+= -g

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
VPATH_DIR		=	./src \


vpath %.c $(VPATH_DIR)

# ----------------------------------
# Source & Object file
# ----------------------------------

SRCS			=	minishell.c \


OBJS			= $(addprefix $(OBJ_DIR)/, ${SRCS:.c=.o})

# ----------------------------------
# Library
# ----------------------------------

LIBFT			= $(LIBFT_DIR)/libft.a
LDFLAGS			= -lft

# ----------------------------------
# Rules
# ----------------------------------

all:			$(NAME)

$(OBJ_DIR):
					@$(MKDIR) $@
					@$(ECHO) "$(GREEN)[Success]\t $(ORANGE)Create $(OBJ_DIR)$(NOCOLOR)"

$(OBJ_DIR)/%.o: %.c
					@$(CC) -c $(CFLAGS) -I$(INC_DIR) -o $@ $^
					@$(ECHO) "$(GREEN)[Success]\t $(ORANGE)Create $@$(NOCOLOR)"

$(LIBFT):
					@$(MAKE) -C $(LIBFT_DIR)

$(NAME):		$(LIBFT) $(OBJ_DIR) ${OBJS}
					@$(CC) $(CFLAGS) -o $@ ${OBJS} $(LDFLAGS)
					@$(ECHO) "$(GREEN)[Success]\t $(BLUE)Create $@ \t$(NOCOLOR)"

clean:
					@$(RM) $(OBJS)
					@$(RMDIR) $(OBJ_DIR)
					@$(ECHO) "$(GREEN)[Success]\t $(RED)Remove $(OBJ_DIR)$(NOCOLOR)"

fclean:			clean
					@$(RM) $(NAME)
					@$(ECHO) "$(GREEN)[Success]\t $(RED)Remove $(NAME)$(NOCOLOR)"

re:				fclean all
