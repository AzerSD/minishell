/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:33:37 by asioud            #+#    #+#             */
/*   Updated: 2023/05/08 06:01:47 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symbol_table/symtab.h"

int pwd(int argc, ...)
{
	struct s_symtab_entry	*s;
	struct s_symtab			*symtab = s_symtab_stack.local_symtab;

	(void) argc;
	s = do_lookup("PWD", symtab);
	if (s)
		printf("%s\n", s->value);
	
	return (0);
}