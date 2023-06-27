/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:33:48 by asioud            #+#    #+#             */
/*   Updated: 2023/06/27 16:42:30 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(int argc, ...)
{
	va_list					args;
	char					**path;
	int						result;
	struct s_symtab_entry	*entry;
	struct s_symtab_entry	*oldpwd;
	struct s_symtab_entry	*pwd;
	char *newpwd;

	entry = NULL;
	if (argc == 1)
	{
		entry = do_lookup("HOME", s_symtab_stack.local_symtab);
		if (entry == NULL)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: cd: HOME not set\n");
			shell.status = 1;
			return (1);
		}
		oldpwd = do_lookup("PWD", s_symtab_stack.local_symtab);
		update_entry(entry, oldpwd->val, "OLDPWD");
		result = chdir(entry->val);
		if (result != 0)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: cd: %s: %s\n", entry->name, strerror(errno));
			shell.status = 1;
			return (1);
		}
		else
			update_entry(entry, entry->val, "PWD");
		shell.status = 0;
		return (0);
	}
	else
	{
		va_start(args, argc);
		path = va_arg(args, char **);
		va_end(args);
		oldpwd = do_lookup("PWD", s_symtab_stack.local_symtab);
		pwd = do_lookup("PWD", s_symtab_stack.local_symtab);
		result = chdir(*(path + 1));
		newpwd = getcwd(NULL, 0);
		update_entry(oldpwd, oldpwd->val, "OLDPWD");
		update_entry(pwd, newpwd, "PWD");

		if (result != 0)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: cd: %s: %s\n", *(path + 1), strerror(errno));
			shell.status = 1;
			return (1);
		}
	}
	shell.status = 0;
	return (0);
}
