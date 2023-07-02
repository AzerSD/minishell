/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 17:26:58 by ygolshan          #+#    #+#             */
/*   Updated: 2023/07/02 17:27:42 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			strcpy(val2, val);
		else
			fprintf(stderr,
				"error: no memory for symbol table entry's value\n");
		entry->val = val2;
	}
}
