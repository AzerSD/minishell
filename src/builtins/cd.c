/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:33:48 by asioud            #+#    #+#             */
/*   Updated: 2023/06/08 18:30:09 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symbol_table/symtab.h"

int cd(int argc, ...)
{
    va_list args;
    char    **path;
    int     result;
    struct s_symtab *st = s_symtab_stack.local_symtab;
    struct s_symtab_entry   *entry = NULL;

    if (argc == 1)
    {
        entry = do_lookup("HOME", st);
        if (entry == NULL)
        {
            fprintf(stderr, "cd: HOME not set\n");
            /* check if the output is the same in bash */
            return 1;
        }
        result = chdir(entry->val);
        if (result != 0)
        {
            fprintf(stderr, "cd: %s: %s\n", entry->name, strerror(errno));
            return 1;
        }
        return 0;
    } 
    else
    {
        va_start(args, argc);
        path = va_arg(args, char**);
        va_end(args);
        result = chdir(*(path+1));
        if (result != 0)
        {
            fprintf(stderr, "cd: %s: %s\n", *(path+1), strerror(errno));
            return 1;
        }
    }
    return 0;
}


