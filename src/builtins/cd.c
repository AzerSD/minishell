/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:33:48 by asioud            #+#    #+#             */
/*   Updated: 2023/06/08 18:44:20 by lhasmi           ###   ########.fr       */
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
#include "../core/shell.h"

#include <unistd.h>
#include <stdio.h>

int	cd(int argc, ...)
{
	va_list					args;
	char					**path;
	int						result;
	struct s_symtab			*st;
	struct s_symtab_entry	*entry;

	st = s_symtab_stack.local_symtab;
	entry = NULL;
	if (argc == 1)
	{
		entry = do_lookup("HOME", st);
		if (entry == NULL)
		{
			fprintf(stderr, "cd: HOME not set\n");
			/* check if the output is the same in bash */
			return (1);
		}
		result = chdir(entry->val);
		if (result != 0)
		{
			fprintf(stderr, "cd: %s: %s\n", entry->name, strerror(errno));
			return (1);
		}
		return (0);
	}
	else
	{
		va_start(args, argc);
		path = va_arg(args, char **);
		va_end(args);
		result = chdir(*(path + 1));
		if (result != 0)
		{
			fprintf(stderr, "cd: %s: %s\n", *(path + 1), strerror(errno));
			return (1);
		}
	}
	return (0);
}
