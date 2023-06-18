/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:33:48 by asioud            #+#    #+#             */
/*   Updated: 2023/06/18 20:12:02 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_cd(struct s_symtab *st, struct s_symtab_entry *entry,
			const char *path);
char	**handle_variadic_args(int argc, ...);

int	ft_cd(int argc, ...)
{
	struct s_symtab			*st;
	struct s_symtab_entry	*entry;
	char					**path;

	entry = NULL;
	st = s_symtab_stack.local_symtab;
	if (argc == 1)
	{
		entry = do_lookup("HOME", st);
		if (entry == NULL)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return (1);
		}
		return (handle_cd(st, entry, entry->val));
	}
	else
	{
		path = handle_variadic_args(argc);
		return (handle_cd(st, entry, *(path + 1)));
	}
}

int	handle_cd(struct s_symtab *st, struct s_symtab_entry *entry,
		const char *path)
{
	struct s_symtab_entry	*oldpwd;
	char					*newpwd;
	int						result;

	oldpwd = do_lookup("PWD", st);
	result = chdir(path);
	newpwd = getcwd(NULL, 0);
	update_entry(entry, oldpwd->val, "OLDPWD");
	update_entry(entry, newpwd, "PWD");
	if (result != 0)
	{
		fprintf(stderr, "cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	return (0);
}

char	**handle_variadic_args(int argc, ...)
{
	va_list	args;
	char	**path;

	va_start(args, argc);
	path = va_arg(args, char **);
	va_end(args);
	return (path);
}

// int	ft_cd(int argc, ...)
// {
// 	va_list					args;
// 	char					**path;
// 	int						result;
// 	struct s_symtab			*st;
// 	struct s_symtab_entry	*entry;
// 	struct s_symtab_entry	*oldpwd;
// 	char					*newpwd;

// 	st = s_symtab_stack.local_symtab;
// 	entry = NULL;
// 	if (argc == 1)
// 	{
// 		entry = do_lookup("HOME", st);
// 		if (entry == NULL)
// 		{
// 			fprintf(stderr, "cd: HOME not set\n");
// 			return (1);
// 		}
// 		oldpwd = do_lookup("PWD", st);
// 		result = chdir(entry->val);
// 		newpwd = getcwd(NULL, 0);
// 		update_entry(entry, oldpwd->val, "OLDPWD");
// 		update_entry(entry, newpwd, "PWD");
// 		if (result != 0)
// 		{
// 			fprintf(stderr, "cd: %s: %s\n", entry->name, strerror(errno));
// 			return (1);
// 		}
// 		return (0);
// 	}
// 	else
// 	{
// 		va_start(args, argc);
// 		path = va_arg(args, char **);
// 		va_end(args);
// 		oldpwd = do_lookup("PWD", st);
// 		result = chdir(*(path + 1));
// 		newpwd = getcwd(NULL, 0);
// 		update_entry(entry, oldpwd->val, "OLDPWD");
// 		update_entry(entry, newpwd, "PWD");
// 		if (result != 0)
// 		{
// 			fprintf(stderr, "cd: %s: %s\n", *(path + 1), strerror(errno));
// 			return (1);
// 		}
// 	}
// 	return (0);
// }
