# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/25 10:59:44 by asioud            #+#    #+#              #
#    Updated: 2023/07/03 21:25:31 by asioud           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
RM			=	rm -rf
LIBFT		= 	libs/libft/libft.a
GC			=	libs/garbage_collector/garbage_collector.a
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
		symbol_table/symtab_stack \
		symbol_table/symtab \
		symbol_table/init_symtab \
		symbol_table/free_symtab \
		symbol_table/symtab_utils \
		\
		builtins/cd \
		builtins/pwd \
		builtins/env \
		builtins/echo \
		builtins/exit \
		builtins/unset \
		builtins/export \
		builtins/builtins \
		\
		execution/executor \
		execution/path \
		execution/pipeline \
		execution/redirections \
		execution/exec_utils \
		\
		parsing/lexer \
		parsing/node \
		parsing/parser \
		parsing/ast_parser \
		parsing/tokenizer \
		parsing/token_handlers \
		parsing/tokenizer_utils \
		parsing/token_handlers2 \
		parsing/heredoc_pipe \
		parsing/p_heredoc \
		\
		expansion/expansion \
		expansion/substitution/command \
		expansion/substitution/utils \
		expansion/substitution/word \
		expansion/substitution/quote_removal \
		expansion/filename \
		expansion/helper_functions \
		expansion/expansion_check \
		expansion/strings \
		expansion/tilde \
		expansion/variable \
		expansion/pattern \
		expansion/pattern_utils \
		expansion/utils \
		expansion/variable_utils \
		\
		signals/signals \
		signals/utils \


SRC_DIR		=	src/
OBJ_DIR		=	obj/


SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC)))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))

all:	$(NAME)


$(NAME): $(OBJS)
	cd libs/libft && make
	cd libs/garbage_collector && make
	$(CC) $(HEADER_FILES) -lreadline -lhistory $(CFLAGS) $(OBJS) $(GC) $(LIBFT) -o $(NAME) $(INCL_RDL_LIB)


$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(HEADER_FILES) $(INCL_RDL_HEADER) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)

fclean:	clean
	@cd libs/libft && make fclean
	@cd libs/garbage_collector && make fclean
	@$(RM) $(NAME)

re:	fclean all

.PHONY:	all bonus clean fclean re
