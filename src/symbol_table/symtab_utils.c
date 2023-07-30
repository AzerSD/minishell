/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 00:26:03 by asioud            #+#    #+#             */
/*   Updated: 2023/07/03 20:23:11 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_entry(struct s_symtab_entry *entry, char *new_val, char *name)
{
	entry = do_lookup(name, g_shell.s_symtab_stack.local_symtab);
	if (!entry)
	{
		entry = add_to_symtab(name);
	}
	symtab_entry_setval(entry, new_val);
}

void	symtab_entry_setval(struct s_symtab_entry *entry, char *val)
{
	char	*val2;

	if (entry->val)
	{
		free(entry->val);
	}
	if (!val)
	{
		entry->val = NULL;
	}
	else
	{
		val2 = my_malloc(&g_shell.memory, strlen(val) + 1);
		if (val2)
		{
			strcpy(val2, val);
		}
		else
		{
			ft_printf_fd(STDERR_FILENO,
				"error: no memory for symbol table entry's value\n");
		}
		entry->val = val2;
	}
}

struct s_symtab_entry	*get_symtab_entry(const char *str)
{
	int						i;
	struct s_symtab			*symtab;
	struct s_symtab_entry	*entry;

	i = g_shell.s_symtab_stack.symtab_count - 1;
	while (i >= 0)
	{
		symtab = g_shell.s_symtab_stack.symtab_list[i];
		entry = do_lookup(str, symtab);
		if (entry)
		{
			return (entry);
		}
		i--;
	}
	return (NULL);
}

int	remove_entry_from_symtab(struct s_symtab_entry *entry, \
		struct s_symtab *symtab)
{
	int	res;

	res = 0;
	if (symtab->first == entry)
	{
		symtab->first = symtab->first->next;
		if (symtab->last == entry)
			symtab->last = NULL;
		res = 1;
	}
	else
	{
		res = remove_subsequent_entry(entry, symtab);
	}
	return (res);
}
