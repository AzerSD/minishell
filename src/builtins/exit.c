/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:34:49 by asioud            #+#    #+#             */
/*   Updated: 2023/07/27 15:55:47 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(int argc, ...)
{
	va_list	args;
	int		exit_code;

	if (argc > 1)
	{
		va_start(args, argc);
		va_arg(args, int);
		exit_code = va_arg(args, int);
		va_end(args);
		g_status = exit_code;
		exit(exit_code);
	}
	g_status = 0;
	exit(0);
}
