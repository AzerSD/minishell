/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:34:19 by asioud            #+#    #+#             */
/*   Updated: 2023/06/16 01:40:17 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symbol_table/symtab.h"

int ft_env(int argc, ...)
{
    (void) argc;
	struct s_symtab *symtab = s_symtab_stack.local_symtab;
	struct s_symtab_entry *entry = symtab->first;

	while (entry)
	{
		fprintf(stderr, "%s=%s\n", entry->name, entry->val);
		entry = entry->next;
	}
    return 0;
}