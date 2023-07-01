/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab_stack2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 16:03:16 by ygolshan          #+#    #+#             */
/*   Updated: 2023/07/01 17:27:46 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_symtab_stack	s_symtab_stack = {0};

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
	struct s_symtab_stack	*symtab_stack;

	symtab_stack = malloc(sizeof(struct s_symtab_stack));
	if (symtab_stack == NULL)
		return (NULL);
	return (symtab_stack);
}
