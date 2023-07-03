/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:33:37 by asioud            #+#    #+#             */
/*   Updated: 2023/07/03 17:44:59 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(int argc, ...)
{
	struct s_symtab_entry	*s;
	struct s_symtab			*symtab;

	symtab = shell.s_symtab_stack.local_symtab;
	(void)argc;
	s = do_lookup("PWD", symtab);
	if (s)
		ft_printf_fd(1, "%s\n", s->val);
	shell.status = 0;
	return (0);
}
