/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:33:25 by asioud            #+#    #+#             */
/*   Updated: 2023/04/29 00:58:37 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

int				echo(int    argc, ...)
{
	int		i;
	int		n_option;
	char	**argv;
	va_list	args;
	va_start(args, argc);
	argv = va_arg(args, char**);

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
			ft_putstr_fd(argv[i], 1);
			if (argv[i + 1] && argv[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (n_option == 0)
		write(1, "\n", 1);
	va_end(args);
	return (0);
}