/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 22:31:33 by asioud            #+#    #+#             */
/*   Updated: 2023/06/16 22:31:33 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RESET "\033[0m"
# define RED "\033[31m" // Red
# define GRN "\033[32m" // Green
# define YEL "\033[33m" // Yellow
# define BLU "\033[34m" // Blue
# define MAG "\033[35m" // Magenta
# define CYN "\033[36m" // Cyan
# define WHT "\033[37m" // White

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




#endif