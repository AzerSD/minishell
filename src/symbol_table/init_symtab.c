/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_symtab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 05:28:17 by asioud            #+#    #+#             */
/*   Updated: 2023/06/08 20:11:16 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../core/shell.h"
#include "../parsing/node.h"
#include "../parsing/parser.h"
#include "symtab.h"

void string_to_symtab(const char *env_var)
{
    struct s_symtab_entry *entry;
    char *eq = strchr(env_var, '=');

    if (eq)
    {
        int len = eq - env_var;
        char name[len + 1];
        strncpy(name, env_var, len);
        name[len] = '\0';
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

void init_symtab(void)
{
    init_symtab_stack();
    char **p2 = environ; /* user env variables @see printenv */
    while (*p2)
    {
        string_to_symtab(*p2);
        p2++;
    }
}

void init_symtab_stack(void)
{
	struct s_symtab	*global_symtab;

	global_symtab = malloc(sizeof(struct s_symtab));

	s_symtab_stack.symtab_count = 1;
	symtab_level = 0;
	if (!global_symtab)
	{
		fprintf(stderr, "fatal error: no memory for global symbol table\n");
		exit(EXIT_FAILURE);
	}
	memset(global_symtab, 0, sizeof(struct s_symtab));
	s_symtab_stack.global_symtab	= global_symtab;
	s_symtab_stack.local_symtab		= global_symtab;
	s_symtab_stack.symtab_list[0]	= global_symtab;
	global_symtab->level			= 0;
}

struct s_symtab *new_symtab(int level)
{
    struct s_symtab *symtab = malloc(sizeof(struct s_symtab));
    if (!symtab)
    {
        fprintf(stderr, "fatal error: no memory for new symbol table\n");
        exit(EXIT_FAILURE);
    }
    memset(symtab, 0, sizeof(struct s_symtab));
    symtab->level = level;
    return symtab;
}
