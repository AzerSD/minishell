/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 11:22:52 by asioud            #+#    #+#             */
/*   Updated: 2023/06/18 20:13:31 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

typedef struct s_env
{
	char				*value;
	struct s_env		*next;
}						t_env;

/* shell builtin utilities */
int						ft_exit(int argc, ...);
int						ft_unset(int argc, ...);
int						ft_dump(int argc, ...);
int						ft_echo(int argc, ...);
int						ft_env(int argc, ...);
int						ft_pwd(int argc, ...);
int						ft_cd(int argc, ...);
int						ft_export(int argc, ...) __attribute__((unused));

//  struct for builtin utilities  utility name
//  function to call to execute the utility
struct					s_builtin
{
	char				*name;
	int					(*func)(int argc, ...);
};

/* the list of builtin utilities */
extern struct s_builtin	builtins[];

/* and their count */
extern int				builtins_count;

// readline, rl_clear_history, rl_on_new_line,
// rl_replace_line, rl_redisplay, add_history,
// printf, malloc, free, write, access, open, read,
// close, fork, wait, waitpid, wait3, wait4, signal,
// sigaction, sigemptyset, sigaddset, kill, exit,
// getcwd, chdir, stat, lstat, fstat, unlink, execve,
// dup, dup2, pipe, opendir, readdir, closedir,
// strerror, perror, isatty, ttyname, ttyslot, ioctl,
// getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
// tgetnum, tgetstr, tgoto, tputs
#endif
