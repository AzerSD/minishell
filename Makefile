# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/25 10:59:44 by asioud            #+#    #+#              #
#    Updated: 2023/06/17 00:16:25 by asioud           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
RM			=	rm -rf
LIBFT		= 	libs/libft/libft.a
CFLAGS		=	-g
HEADER_FILES=	-I ./includes -I ./libs/libft/includes

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
		symbol_table/init_symtab \
		symbol_table/symtab \
		symbol_table/free_symtab \
		symbol_table/symtab_stack \
		\
		builtins/cd \
		builtins/pwd \
		builtins/env \
		builtins/echo \
		builtins/dump \
		builtins/exit \
		builtins/unset \
		builtins/export \
		builtins/builtins \
		prompt/prompt \
		\
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
	$(CC) $(HEADER_FILES) -lreadline -lhistory $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(INCL_RDL_LIB)


$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(HEADER_FILES) $(INCL_RDL_HEADER) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)

fclean:	clean
	@$(RM) $(NAME)

re:	fclean all

.PHONY:	all bonus clean fclean re
