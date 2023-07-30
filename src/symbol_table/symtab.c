/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 07:28:23 by asioud            #+#    #+#             */
/*   Updated: 2023/07/03 20:23:12 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_symtab(void)
{
	struct s_symtab			*symtab;
	struct s_symtab_entry	*entry;

	symtab = g_shell.s_symtab_stack.local_symtab;
	entry = symtab->first;
	while (entry)
	{
		if (is_valid_variable_name(entry->name))
		{
			if (entry->val)
				ft_printf_fd(STDERR_FILENO, "declare -x %s=%s\n", \
				entry->name, entry->val);
			else
				ft_printf_fd(STDERR_FILENO, "declare -x %s\n", entry->name);
		}
		entry = entry->next;
	}
}

void	add_entry_to_symtab(struct s_symtab *st, struct s_symtab_entry *entry)
{
	if (!st->first)
	{
		st->first = entry;
		st->last = entry;
	}
	else
	{
		st->last->next = entry;
		st->last = entry;
	}
}

int	rem_from_symtab(struct s_symtab_entry *entry, struct s_symtab *symtab)
{
	int	res;

	res = remove_entry_from_symtab(entry, symtab);
	if (res == 1)
	{
		free_symtab_entry(entry);
	}
	return (res);
}

struct s_symtab_entry	*do_lookup(const char *str, struct s_symtab *symtable)
{
	struct s_symtab_entry	*entry;

	if (!str || !symtable)
		return (NULL);
	entry = symtable->first;
	while (entry)
	{
		if (strcmp(entry->name, str) == 0)
			return (entry);
		entry = entry->next;
	}
	return (NULL);
}
