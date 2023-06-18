/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:33:25 by asioud            #+#    #+#             */
/*   Updated: 2023/06/18 19:07:40 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The echo command in a shell prints its arguments followed by a newline.
// When the -n option is given, the trailing newline is suppressed.
// shell should parse command-line arguments before passing them to the echo().
#include "minishell.h"

int	ft_echo(int argc, ...)
{
	int		i;
	int		n_option;
	char	**argv;
	va_list	args;

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
