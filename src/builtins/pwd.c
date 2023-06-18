/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:33:37 by asioud            #+#    #+#             */
/*   Updated: 2023/06/18 19:07:10 by lhasmi           ###   ########.fr       */
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
	return (0);
}
