# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/25 10:59:44 by asioud            #+#    #+#              #
#    Updated: 2023/06/13 05:01:41 by asioud           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
RM			=	rm -rf
LIBFT		= 	libs/libft/libft.a
CFLAGS		=	-Wall -Wextra -Werror -g

ifeq ($(OS), Linux)
INCL_RDL_HEADER	= -I /home/linuxbrew/.linuxbrew/opt/readline/include/readline
INCL_RDL_LIB	= -lreadline -L /home/linuxbrew/.linuxbrew/opt/readline/lib
else
INCL_RDL_HEADER	= -I /Users/$(USER)/.brew/opt/readline/include
INCL_RDL_LIB	= -lreadline -L /Users/$(USER)/.brew/opt/readline/lib
endif

BREW			= /Users/$(USER)/.brew/bin
READLINE		= /Users/$(USER)/.brew/opt/readline/include/readline

SRC	=	core/shell \
		\
		builtins/cd \
		builtins/pwd \
		builtins/env \
		builtins/echo \
		builtins/dump \
		builtins/exit_builtin \
		builtins/unset \
		builtins/export_builtin \
		builtins/builtins \
		\
		prompt/prompt \
		\
		symbol_table/init_symtab \
		symbol_table/symtab \
		symbol_table/free_symtab \
		symbol_table/symtab_stack \
		\
		execution/executor \
		execution/path \
		\
		parsing/lexer \
		parsing/node \
		parsing/parser \
		parsing/tokenizer \
		parsing/token_handlers \
		\
		expansion/expansion \
		expansion/command_substitution \
		expansion/filename \
		expansion/helper_functions \
		expansion/quote_removal \
		expansion/strings \
		expansion/tilde \
		expansion/variable \
		expansion/pattern \
		\
		signals/signals \


SRC_DIR		=	src/
OBJ_DIR		=	obj/


SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC)))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))

all:	$(NAME)


$(NAME): $(OBJS)
	$(CC) -lreadline -lhistory  $(INCL_RDL_LIB) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)


$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(INCL_RDL_HEADER) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)

fclean:	clean
	@$(RM) $(NAME)

re:	fclean all

.PHONY:	all bonus clean fclean re
