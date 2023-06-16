/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:34:49 by asioud            #+#    #+#             */
/*   Updated: 2023/06/16 22:36:05 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_exit(int argc, ...)
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
