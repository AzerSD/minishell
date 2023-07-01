/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:20:30 by ygolshan          #+#    #+#             */
/*   Updated: 2023/07/01 18:05:57 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_symtab_entry	*get_symtab_entry(const char *str)
{
	int						i;
	struct s_symtab			*symtab;
	struct s_symtab_entry	*entry;

	i = s_symtab_stack.symtab_count - 1;
	entry = NULL;
	while (i >= 0 && !entry)
	{
		symtab = s_symtab_stack.symtab_list[i];
		entry = do_lookup(str, symtab);
		i--;
	}
	return (entry);
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
		val2 = my_malloc(&shell.memory, strlen(val) + 1);
		if (val2)
		{
			strcpy(val2, val);
		}
		else
		{
			fprintf(stderr,
				"error: no memory for symbol table entry's value\n");
		}
		entry->val = val2;
	}
}

void	update_entry(struct s_symtab_entry *entry,
	char *new_val, char *name)
{
	entry = do_lookup(name, s_symtab_stack.local_symtab);
	if (!entry)
	{
		entry = add_to_symtab(name);
	}
	symtab_entry_setval(entry, new_val);
}
