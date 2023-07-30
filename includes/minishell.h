/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:28:46 by asioud            #+#    #+#             */
/*   Updated: 2023/06/19 18:28:46 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RESET "\001\033[0m\002"
# define RED "\001\033[31m\002" // Red
# define GRN "\001\033[32m\002" // Green
# define YEL "\001\033[33m\002" // Yellow
# define BLU "\001\033[34m\002" // Blue
# define MAG "\001\033[35m\002" // Magenta
# define CYN "\001\033[36m\002" // Cyan
# define WHT "\001\033[37m\002" // White

# include <unistd.h>
# include <limits.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <termios.h>
# include <stdbool.h>
# include <glob.h> // https://c-for-dummies.com/blog/?p=4782
# include <ctype.h>
# include <dirent.h>
# include <regex.h>
# include <fnmatch.h>
# include <pwd.h>
# include <locale.h>
# include <readline/history.h>
# include <readline/readline.h>

# include "libft.h"
# include "../src/symbol_table/symtab.h"
# include "../src/parsing/lexer.h"
# include "../src/parsing/node.h"
# include "../src/parsing/tokenizer.h"
# include "../src/builtins/builtins.h"
# include "../src/parsing/parser.h"
# include "../src/execution/executor.h"
# include "../src/expansion/expansion.h"
# include "../src/core/shell.h"
# include "../src/signals/signals.h"
# include "../libs/garbage_collector/memory.h"

typedef unsigned char		t_status;

typedef struct g_shell
{
	t_status				status;
	void					*memory;
	struct s_symtab_stack	s_symtab_stack;
}	t_shell;

t_shell						g_shell;

#endif