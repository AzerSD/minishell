/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:34:19 by asioud            #+#    #+#             */
/*   Updated: 2023/06/19 20:01:44 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_env(int argc, ...)
{
    (void) argc;
	struct s_symtab *symtab = s_symtab_stack.local_symtab;
	struct s_symtab_entry *entry = symtab->first;

	while (entry)
	{
		if (is_valid_variable_name(entry->name))
			ft_printf_fd(1, "%s=%s\n", entry->name, entry->val);
		entry = entry->next;
	}
    return 0;
}