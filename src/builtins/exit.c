/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:34:49 by asioud            #+#    #+#             */
/*   Updated: 2023/06/18 19:07:19 by lhasmi           ###   ########.fr       */
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
		exit(exit_code);
	}
	exit(0);
}
