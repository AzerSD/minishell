/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 05:13:44 by asioud            #+#    #+#             */
/*   Updated: 2023/06/21 04:49:14 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_argv(int argc, char **argv)
{
	if (!argc)
		return ;
	while (argc--)
		free(argv[argc]);
}

int	wait_for_child(pid_t child_pid)
{
	int	status;

	status = 0;
	waitpid(child_pid, &status, 0);
	return (status);
}
