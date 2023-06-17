/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 11:22:52 by asioud            #+#    #+#             */
/*   Updated: 2023/06/16 22:33:16 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"



typedef struct	s_env
{
	char			*value;
	struct s_env	*next;
}	t_env;

/* shell builtin utilities */
int			ft_exit(int argc, ...);
int			ft_unset(int argc, ...);
int			ft_dump(int argc, ...);
int			ft_echo(int argc, ...);
int			ft_env(int argc, ...);
int			ft_pwd(int argc, ...);
int			ft_cd(int argc, ...);
int			ft_export(int argc, ...) __attribute__((unused));

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
