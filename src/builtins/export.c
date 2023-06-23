/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:33:58 by asioud            #+#    #+#             */
/*   Updated: 2023/06/23 17:37:05 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_export(int argc, ...)
{
    struct s_symtab_entry   *entry = NULL;
    struct s_symtab         *symtab = s_symtab_stack.local_symtab;
    char   **argv;

    va_list args;
    va_start(args, argc);
    argv = va_arg(args, char **);
    entry = symtab->first;
    va_end(args);
    g_status = 0;
    
    if (argc == 1)
    {
        /* display all env vars e.g `declare -x var=value` */
        while (entry)
        {
            fprintf(stderr, "declare -x %s=%s\n", entry->name, entry->val);
            entry = entry->next;
        }
        
        return (g_status = 0, 0);   
    }
    else
    {
        /* display only the env vars passed as arguments */
        va_start(args, argc);
        argv = va_arg(args, char **);
        entry = do_lookup(argv[1], symtab);
        va_end(args);
        if (entry)
            fprintf(stderr, "declare -x %s=%s\n", entry->name, entry->val);
        return (g_status = 1, 1);
    }
}
