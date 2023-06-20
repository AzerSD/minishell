/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:34:08 by asioud            #+#    #+#             */
/*   Updated: 2023/06/20 00:51:16 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_unset(int argc, ...)
{
    va_list args;
    char    **var_name;
	struct s_symtab_entry	*s = NULL;
	struct s_symtab			*symtab = s_symtab_stack.local_symtab;

    if (argc == 1)
        return (g_status = 0, 0);
    else
    {
        va_start(args, argc);
        var_name = va_arg(args, char**);
        var_name++;
        while (*var_name)
        {
            s = do_lookup(*var_name, symtab);
            if (!s) // if variable does not exist
                return (g_status = 1, 1);
            rem_from_symtab(s, symtab);
            var_name++;
        }
        va_end(args);
    }

    return (g_status = 0, 0);
}