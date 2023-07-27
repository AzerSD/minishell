/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:34:19 by asioud            #+#    #+#             */
/*   Updated: 2023/07/27 16:02:42 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(int argc, ...)
{
	struct s_symtab			*symtab;
	struct s_symtab_entry	*entry;

	(void)argc;
	symtab = s_symtab_stack.local_symtab;
	entry = symtab->first;
	while (entry)
	{
		if (is_valid_variable_name(entry->name))
			ft_printf_fd(1, "%s=%s\n", entry->name, entry->val);
		entry = entry->next;
	}
	return (0);
}
