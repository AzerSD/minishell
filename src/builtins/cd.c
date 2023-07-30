/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:33:48 by asioud            #+#    #+#             */
/*   Updated: 2023/07/03 20:22:40 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(char *newpwd)
{
	struct s_symtab_entry	*oldpwd;
	struct s_symtab_entry	*pwd;

	oldpwd = do_lookup("PWD", g_shell.s_symtab_stack.local_symtab);
	pwd = do_lookup("PWD", g_shell.s_symtab_stack.local_symtab);
	update_entry(oldpwd, oldpwd->val, "OLDPWD");
	update_entry(pwd, newpwd, "PWD");
}

int	change_to_home(void)
{
	struct s_symtab_entry	*entry;
	char					*newpwd;
	int						result;

	entry = do_lookup("HOME", g_shell.s_symtab_stack.local_symtab);
	if (entry == NULL)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: cd: HOME not set\n");
		return (1);
	}
	result = chdir(entry->val);
	if (result != 0)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: cd: %s: %s\n", entry->name,
			strerror(errno));
		return (1);
	}
	newpwd = getcwd(NULL, 0);
	update_pwd(newpwd);
	g_shell.status = 0;
	return (0);
}

int	change_to_oldpwd(void)
{
	struct s_symtab_entry	*oldpwd_entry;
	char					*newpwd;
	int						result;

	oldpwd_entry = do_lookup("OLDPWD", g_shell.s_symtab_stack.local_symtab);
	if (oldpwd_entry == NULL)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: cd: OLDPWD not set\n");
		return (1);
	}
	result = chdir(oldpwd_entry->val);
	if (result != 0)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: cd: %s: %s\n",
			oldpwd_entry->val, strerror(errno));
		return (1);
	}
	newpwd = getcwd(NULL, 0);
	update_pwd(newpwd);
	ft_printf_fd(STDOUT_FILENO, "%s\n", newpwd);
	return (0);
}

int	change_to_new_dir(char *new_dir_path)
{
	char	*newpwd;
	int		result;

	result = chdir(new_dir_path);
	if (result != 0)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: cd: %s: %s\n", new_dir_path,
			strerror(errno));
		return (1);
	}
	newpwd = getcwd(NULL, 0);
	update_pwd(newpwd);
	return (0);
}

int	ft_cd(int argc, ...)
{
	va_list	args;
	char	**path;
	int		result;

	result = 0;
	va_start(args, argc);
	path = va_arg(args, char **);
	va_end(args);
	if (argc == 1)
	{
		result = change_to_home();
	}
	else
	{
		if (ft_strcmp(*(path + 1), "-") == 0)
		{
			result = change_to_oldpwd();
		}
		else
		{
			result = change_to_new_dir(*(path + 1));
		}
	}
	return (result);
}
