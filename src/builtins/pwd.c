/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:33:37 by asioud            #+#    #+#             */
/*   Updated: 2023/06/16 01:40:49 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symbol_table/symtab.h"
#include "../core/shell.h"

int ft_pwd(int argc, ...)
{
	struct s_symtab_entry	*s;
	struct s_symtab			*symtab = s_symtab_stack.local_symtab;

	(void) argc;
	s = do_lookup("PWD", symtab);
	if (s)
		printf("%s\n", s->val);
	return (0);
}
