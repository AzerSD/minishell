/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:34:49 by asioud            #+#    #+#             */
/*   Updated: 2023/06/29 09:18:15 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_exit(int argc, ...)
{
    va_list args;
    int     exit_code;
    char **argv;

    va_start(args, argc);
    argv = va_arg(args, char **);
    va_end(args);

    if (argc > 1)
    {
        char *end;
        long long num = strtoll(argv[1], &end, 10);

        if (*end != '\0' || num > INT_MAX || num < INT_MIN) 
        {
            ft_printf_fd(STDERR_FILENO, "minishell: exit: %s: numeric argument required\n", argv[1]);
            shell.status = 255;
            return (255);
        }
        else if (argc > 2) 
        {
            ft_printf_fd(STDERR_FILENO, "minishell: exit: too many arguments\n");
            return 1;
        }
        else 
        {
            exit_code = (int)num;
        }
    }
    else
    {
        exit_code = 0;
    }

    shell.status = exit_code;
    ft_printf_fd(STDERR_FILENO, "exit\n");
    // free_all_mem(&shell.memory);
    exit(exit_code);
}
