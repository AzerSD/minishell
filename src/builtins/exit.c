/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:34:49 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/28 21:47:52 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	parse_exit_args(char **argv)
{
	char		*end;
	long long	num;

	num = strtoll(argv[1], &end, 10);
	if (*end != '\0' || num > INT_MAX || num < INT_MIN)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: exit: \
            %s: numeric argument required\n", argv[1]);
		shell.status = 255;
		return (255);
	}
	return (num);
}

int	check_too_many_args(int argc)
{
	if (argc > 2)
	{
		ft_printf_fd(STDERR_FILENO,
			"minishell: exit: too many arguments\n");
		return (1);
	}
	return (0);
}

void	exit_shell(int exit_code)
{
	shell.status = exit_code;
	ft_printf_fd(STDERR_FILENO, "exit\n");
	exit(exit_code);
}

int	ft_exit(int argc, ...)
{
	va_list		args;
	int			exit_code;
	char		**argv;
	long long	num;

	va_start(args, argc);
	argv = va_arg(args, char **);
	va_end(args);
	if (argc > 1)
	{
		num = parse_exit_args(argv);
		if (num == 255)
			return (255);
		if (check_too_many_args(argc))
			return (1);
		exit_code = (int)num;
	}
	else
	{
		exit_code = 0;
	}
	exit_shell(exit_code);
	return (0);
}
