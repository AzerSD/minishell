/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:33:25 by asioud            #+#    #+#             */
/*   Updated: 2023/06/24 03:15:42 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_echo(int argc, ...)
{
    int i;
    int n_option;
    char **argv;
    va_list args;
    va_start(args, argc);
    argv = va_arg(args, char **);
    if (argc <= 0)
        return (-1);
    i = 1;
    n_option = 0;
    if (argc > 1)
    {
        while (argv[i] && ft_strcmp(argv[i], "-n") == 0)
        {
            n_option = 1;
            i++;
        }
        while (argv[i])
        {
            ft_putstr_fd(argv[i], STDOUT_FILENO);
            if (argv[i + 1] && argv[i][0] != '\0')
                ft_putchar_fd(' ', STDOUT_FILENO);
            i++;
        }
    }
    if (n_option == 0)
        ft_putchar_fd('\n', STDOUT_FILENO);
    va_end(args);
    shell.status = 0;
    return (0);
}
