/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:26:53 by asioud            #+#    #+#             */
/*   Updated: 2023/04/12 19:26:53 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/**
 * @brief adds the given symbol table to the stack, 
 * and assigns the newly added table as the local symbol table.
*/
static void symtab_stack_add(struct s_symtab *symtab)
{
	s_symtab_stack.symtab_list[s_symtab_stack.symtab_count++] = symtab;
	s_symtab_stack.local_symtab = symtab;
}

struct s_symtab *symtab_stack_push(void)
{
	struct s_symtab *st = new_symtab(++symtab_level);
	symtab_stack_add(st);
	return st;
}

struct s_symtab *symtab_stack_pop(void)
{
	if (s_symtab_stack.symtab_count == 0)
		return NULL;
	struct s_symtab *st = s_symtab_stack.symtab_list[s_symtab_stack.symtab_count-1];
	s_symtab_stack.symtab_list[--s_symtab_stack.symtab_count] = NULL;
	symtab_level--;
	if (s_symtab_stack.symtab_count == 0)
	{
		s_symtab_stack.local_symtab  = NULL;
		s_symtab_stack.global_symtab = NULL;
	}
	else
		s_symtab_stack.local_symtab = s_symtab_stack.symtab_list[s_symtab_stack.symtab_count-1];
	return st;
}

struct s_symtab *get_local_symtab(void)
{
	return s_symtab_stack.local_symtab;
}

struct s_symtab *get_global_symtab(void)
{
	return s_symtab_stack.global_symtab;
}

struct s_symtab_stack *get_symtab_stack(void)
{
	return &s_symtab_stack;
}
