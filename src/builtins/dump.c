/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 05:42:20 by asioud            #+#    #+#             */
/*   Updated: 2023/06/08 11:48:58 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#include "../core/shell.h"
#include "../symbol_table/symtab.h"
void dump_local_symtab(void)
{
	struct s_symtab *symtab = s_symtab_stack.local_symtab;
	int i = 0;
	int indent = symtab->level * 4;
	fprintf(stderr, "%*sSymbol table [Level %d]:\r\n", indent, " ", symtab->level);
	fprintf(stderr, "%*s===========================\r\n", indent, " ");
	fprintf(stderr, "%*s  No               Symbol                    Val\r\n", indent, " ");
	fprintf(stderr, "%*s------ -------------------------------- ------------\r\n", indent, " ");
	struct s_symtab_entry *entry = symtab->first;
	while (entry)
	{
		fprintf(stderr, "%*s[%04d] %-32s '%s'\r\n", indent, " ",
				i++, entry->name, entry->val);
		entry = entry->next;
	}
	fprintf(stderr, "%*s------ -------------------------------- ------------\r\n", indent, " ");
}

int dump(int argc, ...)
{
    (void) argc;
    dump_local_symtab();
    return 0;
}