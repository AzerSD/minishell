/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:33:37 by asioud            #+#    #+#             */
/*   Updated: 2023/07/01 17:18:42 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(int argc, ...)
{
	struct s_symtab_entry	*s;
	struct s_symtab			*symtab;


	symtab = s_symtab_stack.local_symtab;
	(void)argc;
	s = do_lookup("PWD", symtab);
	if (s)
		printf("%s\n", s->val);
	shell.status = 0;
	return (0);
}
