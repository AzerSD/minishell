/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 11:22:52 by asioud            #+#    #+#             */
/*   Updated: 2023/05/11 08:13:41 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../core/shell.h"
# include <limits.h>
# include <stdarg.h>


typedef struct	s_env
{
	char			*value;
	struct s_env	*next;
}	t_env;

/* shell builtin utilities */
int		dump(int argc, ...);
int		echo(int argc, ...);
int		env(int argc, ...);
int		pwd(int argc, ...);
int		cd(int argc, ...);


/* struct for builtin utilities */
struct s_builtin
{
	char *name;    /* utility name */
	int (*func)(int argc, ...); /* function to call to execute the utility */
};

/* the list of builtin utilities */
extern struct s_builtin builtins[];

/* and their count */
extern int builtins_count;

#endif