/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:34:49 by asioud            #+#    #+#             */
/*   Updated: 2023/06/08 13:57:11 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symbol_table/symtab.h"
#include "../core/shell.h"

int exit_builtin(int argc, ...)
{
    va_list args;
    int     exit_code;

    if (argc > 1)
    {
        va_start(args, argc);
        va_arg(args, int);
        exit_code = va_arg(args, int);
        va_end(args);
        exit(exit_code);
    }

    exit(0);
}
