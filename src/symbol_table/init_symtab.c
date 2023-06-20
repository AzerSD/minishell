/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_symtab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 05:28:17 by asioud            #+#    #+#             */
/*   Updated: 2023/06/20 00:13:13 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char* get_varname(const char *str)
{
    char* equalsSignPosition = strchr(str, '=');
    if (equalsSignPosition)
	{
        int len = equalsSignPosition - str;
        char *varName = malloc(len + 1);
        strncpy(varName, str, len);
        varName[len] = '\0';
        return varName;
    }
	else
        return NULL;
}

void	string_to_symtab(const char *env_var)
{
	struct s_symtab_entry	*entry;
	char					*eq;
	char *name;
	eq = strchr(env_var, '=');
	if (eq)
	{
		// int len = eq - env_var;
        // char name[len + 1];
		// strncpy(name, env_var, len);
		// name[len] = '\0';
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
	struct s_symtab			*st;

	st = s_symtab_stack.local_symtab;
	init_symtab_stack();
	char **p2 = env;
	while (*p2)
	{
		string_to_symtab(*p2);
		p2++;
	}
	entry = do_lookup("OLDPWD", st);
	// entry = add_to_symtab("?");
	update_entry(entry, NULL, "OLDPWD");
}

void	init_symtab_stack(void)
{
	struct s_symtab	*global_symtab;

	global_symtab = malloc(sizeof(struct s_symtab));
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

struct s_symtab	*new_symtab()
{
	struct s_symtab	*symtab;

	symtab = malloc(sizeof(struct s_symtab));
	if (!symtab)
	{
		fprintf(stderr, "fatal error: no memory for new symbol table\n");
		exit(EXIT_FAILURE);
	}
	memset(symtab, 0, sizeof(struct s_symtab));
	return (symtab);
}
