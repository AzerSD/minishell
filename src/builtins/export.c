/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:33:58 by asioud            #+#    #+#             */
/*   Updated: 2023/07/27 15:59:45 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symbol_table/symtab.h"

int	ft_export(int argc, ...)
{
	struct s_symtab_entry	*entry;
	struct s_symtab			*symtab;
	char					**argv;
	va_list					args;

	entry = NULL;
	symtab = s_symtab_stack.local_symtab;
	va_start(args, argc);
	argv = va_arg(args, char **);
	entry = symtab->first;
	va_end(args);
	if (argc == 1)
	{
		while (entry)
		{
			fprintf(stderr, "declare -x %s=%s\n", entry->name, entry->val);
			entry = entry->next;
		}
		return (g_status = 0, 0);
	}
	else
	{
		va_start(args, argc);
		argv = va_arg(args, char **);
		entry = do_lookup(argv[1], symtab);
		va_end(args);
		if (entry)
			fprintf(stderr, "declare -x %s=%s\n", entry->name, entry->val);
		return (g_status = 1, 1);
	}
}
