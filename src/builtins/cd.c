/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:33:48 by asioud            #+#    #+#             */
/*   Updated: 2023/05/11 08:40:29 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symbol_table/symtab.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int cd(int argc, ...)
{
    va_list args;
    char    **path;
    int     result;

    va_start(args, argc);
    path = va_arg(args, char**);
    va_end(args);
    result = chdir(*(path+1));
    if (result != 0)
    {
        fprintf(stderr, "cd: %s: %s\n", *(path+1), strerror(errno));
        return 1;
    }
    return 0;
}


