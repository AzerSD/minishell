/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:33:48 by asioud            #+#    #+#             */
/*   Updated: 2023/06/08 11:45:42 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// rl_replace_line, rl_redisplay, add_history,
// printf, malloc, free, write, access, open, read,
// close, fork, wait, waitpid, wait3, wait4, signal,
// sigaction, sigemptyset, sigaddset, kill, exit,
// getcwd, chdir, stat, lstat, fstat, unlink, execve,
// dup, dup2, pipe, opendir, readdir, closedir,
// strerror, perror, isatty, ttyname, ttyslot, ioctl,
// getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
// tgetnum, tgetstr, tgoto, tputs
#include "../symbol_table/symtab.h"

#include <unistd.h>
#include <stdio.h>

int ft_cd(int argc, char **argv)
{
    if (argc == 1) 
        return 0;
    if (chdir(argv[1]) < 0)
    {
        fprintf(stderr, "cd: %s: %s\n", argv[1], strerror(errno));
        return 1;
    }
    return 0;
}

        // perror("cd");
// int cd(int argc, ...)
// {
//     va_list args;
//     char    **path;
//     int     result;

//     va_start(args, argc);
//     path = va_arg(args, char**);
//     va_end(args);
//     result = chdir(*(path+1));
//     if (result != 0)
//     {
//         fprintf(stderr, "cd: %s: %s\n", *(path+1), strerror(errno));
//         return 1;
//     }
//     return 0;
// }


