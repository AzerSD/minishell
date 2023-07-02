/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab_stack2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 11:53:49 by ygolshan          #+#    #+#             */
/*   Updated: 2023/07/02 12:04:40 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// struct s_symtab_stack	s_symtab_stack = {0};

// static void	symtab_stack_add(struct s_symtab *symtab)
// {
// 	s_symtab_stack.symtab_list[s_symtab_stack.symtab_count++] = symtab;
// 	s_symtab_stack.local_symtab = symtab;
// }

// struct s_symtab	*symtab_stack_push(void)
// {
// 	struct s_symtab	*st;

// 	st = new_symtab();
// 	symtab_stack_add(st);
// 	return (st);
// }

struct s_symtab	*symtab_stack_pop(void)
{
	struct s_symtab	*st;

	st = s_symtab_stack.symtab_list[s_symtab_stack.symtab_count - 1];
	if (s_symtab_stack.symtab_count == 0)
		return (NULL);
	s_symtab_stack.symtab_list[--s_symtab_stack.symtab_count] = NULL;
	if (s_symtab_stack.symtab_count == 0)
	{
		s_symtab_stack.local_symtab = NULL;
		s_symtab_stack.global_symtab = NULL;
	}
	else
		s_symtab_stack.local_symtab
			= s_symtab_stack.symtab_list[s_symtab_stack.symtab_count - 1];
	return (st);
}
