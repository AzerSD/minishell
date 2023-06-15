/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 05:41:31 by asioud            #+#    #+#             */
/*   Updated: 2023/06/16 01:44:57 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/**
 * A builtin utility (a.k.a. builtin or internal command) is a command whose
 * code is compiled as part of the shell executable itself, i.e. the shell
 * doesn’t need to execute an external program, nor does it need to fork a
 * new process in order to execute the command. Many of the commands we use
 * on daily basis, such as cd, echo, export, and readonly are in fact builtin
 * utilities. You can read more about shell builtin utilities in this POSIX
 * standard.
 *https://www.gnu.org/software/bash/manual/html_node/Shell-Builtin-Commands.html
 When the name of a built-in command is used as the first word of a simple command,
 the shell executes the command directly, without invoking another program.
 You will need to code echo (with the n option) done
 , cd, pwd, export, unset, env, and exit
 as built-in commands in your shell.
 This will likely involve writing a function to code its expected behavior.
 */
//  readline, rl_clear_history, rl_on_new_line,
// rl_replace_line, rl_redisplay, add_history,
// printf, malloc, free, write, access, open, read,
// close, fork, wait, waitpid, wait3, wait4, signal,
// sigaction, sigemptyset, sigaddset, kill, exit,
// getcwd, chdir, stat, lstat, fstat, unlink, execve,
// dup, dup2, pipe, opendir, readdir, closedir,
// strerror, perror, isatty, ttyname, ttyslot, ioctl,
// getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
// tgetnum, tgetstr, tgoto, tputs
#include"builtins.h"

struct s_builtin builtins[] =
{
    { "dump"    , ft_dump },
    { "echo"    , ft_echo },
    { "env"     , ft_env },
    { "pwd"     , ft_pwd },
    { "cd"      , ft_cd }, /* lacking changing pwd and old_pwd*/
    { "export"  , ft_export },
    { "unset"   , ft_unset },
    { "exit"    , ft_exit },
};

int builtins_count = sizeof(builtins) / sizeof(struct s_builtin);
