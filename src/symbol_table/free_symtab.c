/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_symtab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/04/12 19:24:17 by asioud            #+#    #+#             */
/*   Updated: 2023/04/12 19:24:17 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	free_symtab(struct s_symtab *symtab)
{
	struct s_symtab_entry	*entry;
	struct s_symtab_entry	*next;

	next = entry->next;
	entry = symtab->first;
	if (symtab == NULL)
		return ;

	while (entry)
	{
		if (entry->name)
			free(entry->name);
		if (entry->val)
			free(entry->val);
		if (entry->func_body)
			free_node_tree(entry->func_body);

		free(entry);
		entry = next;
	}
	free(symtab);
}
