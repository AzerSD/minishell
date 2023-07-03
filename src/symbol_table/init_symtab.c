/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_symtab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 05:28:17 by asioud            #+#    #+#             */
/*   Updated: 2023/07/02 23:57:49 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_varname(const char *str)
{
	char	*eq;
	int		len;
	char	*var_name;

	eq = strchr(str, '=');
	if (eq)
	{
		len = eq - str;
		var_name = my_malloc(&shell.memory, len + 1);
		strncpy(var_name, str, len);
		var_name[len] = '\0';
		return (var_name);
	}
	else
		return (NULL);
}

void	string_to_symtab(const char *env_var)
{
	struct s_symtab_entry	*entry;
	char					*eq;
	char					*name;

	eq = strchr(env_var, '=');
	if (eq)
	{
		name = get_varname(env_var);
		entry = add_to_symtab(name);
		if (entry)
			symtab_entry_setval(entry, eq + 1);
	}
	else
	{
		entry = add_to_symtab(env_var);
		if (entry)
			symtab_entry_setval(entry, NULL);
	}
}

void	init_symtab(char **env)
{
	struct s_symtab_entry	*entry;
	char					**p2;

	init_symtab_stack();
	p2 = env;
	while (*p2)
	{
		string_to_symtab(*p2);
		p2++;
	}
	entry = do_lookup("OLDPWD", s_symtab_stack.local_symtab);
	if (entry)
		rem_from_symtab(entry, s_symtab_stack.local_symtab);
}

void	init_symtab_stack(void)
{
	struct s_symtab	*global_symtab;

	global_symtab = my_malloc(&shell.memory, sizeof(struct s_symtab));
	s_symtab_stack.symtab_count = 1;
	if (!global_symtab)
	{
		fprintf(stderr, "fatal error: no memory for global symbol table\n");
		exit(EXIT_FAILURE);
	}
	memset(global_symtab, 0, sizeof(struct s_symtab));
	s_symtab_stack.global_symtab = global_symtab;
	s_symtab_stack.local_symtab = global_symtab;
	s_symtab_stack.symtab_list[0] = global_symtab;
}

struct s_symtab	*new_symtab(void)
{
	struct s_symtab	*symtab;

	symtab = my_malloc(&shell.memory, sizeof(struct s_symtab));
	if (!symtab)
	{
		fprintf(stderr, "fatal error: no memory for new symbol table\n");
		exit(EXIT_FAILURE);
	}
	memset(symtab, 0, sizeof(struct s_symtab));
	return (symtab);
}
