/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:33:25 by asioud            #+#    #+#             */
/*   Updated: 2023/06/16 22:35:33 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The echo command in a shell prints its arguments followed by a newline. 
// When the -n option is given, the trailing newline is suppressed.
// shell should parse command-line arguments before passing them to the echo().
#include "minishell.h"

int				ft_echo(int    argc, ...)
{
	int		i;
	int		n_option;
	char	**argv;
	va_list	args;
	va_start(args, argc);
	argv = va_arg(args, char**);
	// Error check for argc
	if (argc <= 0)
		return (-1);
	i = 1;
	n_option = 0;
	// Checking for "-n" option
	if (argc > 1)
	{
		while (argv[i] && ft_strcmp(argv[i], "-n") == 0)
		{
			n_option = 1;
			i++;
		}
		//printing each argv
		while (argv[i])
		{
			ft_putstr_fd(argv[i], 1);
			if (argv[i + 1] && argv[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	//printing a new liine if -n is not present
	if (n_option == 0)
		write(1, "\n", 1);
	va_end(args);
	return (0);
}