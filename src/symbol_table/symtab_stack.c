/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 00:13:03 by lhasmi            #+#    #+#             */
/*   Updated: 2023/08/19 00:13:03 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_symtab_stack	s_symtab_stack = {0};

static void	symtab_stack_add(struct s_symtab *symtab)
{
	s_symtab_stack.symtab_list[s_symtab_stack.symtab_count++] = symtab;
	s_symtab_stack.local_symtab = symtab;
}

struct s_symtab	*symtab_stack_push(void)
{
	struct s_symtab *st = new_symtab();
	symtab_stack_add(st);
	return (st);
}

struct s_symtab	*symtab_stack_pop(void)
{
	if (s_symtab_stack.symtab_count == 0)
		return (NULL);
	struct s_symtab *st = s_symtab_stack.symtab_list[s_symtab_stack.symtab_count
		- 1];
	s_symtab_stack.symtab_list[--s_symtab_stack.symtab_count] = NULL;
	if (s_symtab_stack.symtab_count == 0)
	{
		s_symtab_stack.local_symtab = NULL;
		s_symtab_stack.global_symtab = NULL;
	}
	else
		s_symtab_stack.local_symtab = s_symtab_stack.symtab_list[s_symtab_stack.symtab_count
			- 1];
	return (st);
}

struct s_symtab	*get_local_symtab(void)
{
	return (s_symtab_stack.local_symtab);
}

struct s_symtab	*get_global_symtab(void)
{
	return (s_symtab_stack.global_symtab);
}

struct s_symtab_stack	*get_symtab_stack(void)
{
	return (&s_symtab_stack);
}
