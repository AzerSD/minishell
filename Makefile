# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/25 10:59:44 by asioud            #+#    #+#              #
#    Updated: 2023/06/09 18:10:25 by lhasmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
RM			=	rm -rf
LIBFT		= 	libs/libft/libft.a
CFLAGS		=	-Wall -Wextra -Werror -g


INCL_RDL_HEADER	= -I /Users/$(USER)/.brew/opt/readline/include
INCL_RDL_LIB	= -lreadline -L /Users/$(USER)/.brew/opt/readline/lib

BREW			= /Users/$(USER)/.brew/bin
READLINE		= /Users/$(USER)/.brew/opt/readline/include/readline

SRC	=	core/shell \
		\
		builtins/builtins	builtins/dump \
		builtins/echo \
		builtins/cd \
		builtins/env \
		builtins/pwd \
		builtins/exit_builtin \
		builtins/unset \
		builtins/export_builtin \
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
	$(CC)  -lreadline -lhistory $(INCL_RDL_LIB) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)


$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(INCL_RDL_HEADER) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)

fclean:	clean
	@$(RM) $(NAME)

re:	fclean all

.PHONY:	all bonus clean fclean re
