/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 01:54:40 by asioud            #+#    #+#             */
/*   Updated: 2023/04/23 05:29:07 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../core/shell.h"
#include "../symbol_table/symtab.h"

void prompt_display_ps1(void)
{
    struct s_symtab_entry *entry = get_symtab_entry("PS1");
    if (entry && entry->val)
        fprintf(stderr, "%s", entry->val);
    else
        fprintf(stderr, "\033[1;32m$ ");
}

void prompt_display_ps2(void)
{
    struct s_symtab_entry *entry = get_symtab_entry("PS2");

    if (entry && entry->val)
        fprintf(stderr, "%s", entry->val);
    else
        fprintf(stderr, "\033[1;32m> ");
}

