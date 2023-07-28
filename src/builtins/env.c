/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:34:19 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/28 21:47:45 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(int argc, ...)
{
	va_list					args;
	char					**argv;
	struct s_symtab			*symtab;
	struct s_symtab_entry	*entry;

	va_start(args, argc);
	argv = va_arg(args, char **);
	va_end(args);
	if (argc > 1)
	{
		exec_cmd(argc - 1, argv + 1);
		return (0);
	}
	else
	{
		symtab = shell.s_symtab_stack.local_symtab;
		entry = symtab->first;
		while (entry)
		{
			if (is_valid_variable_name(entry->name))
				ft_printf_fd(STDOUT_FILENO, "%s=%s\n", entry->name, entry->val);
			entry = entry->next;
		}
		return (0);
	}
}
