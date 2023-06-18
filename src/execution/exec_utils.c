/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 05:13:44 by asioud            #+#    #+#             */
/*   Updated: 2023/06/18 02:37:12 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


void free_argv(int argc, char **argv)
{
	if (!argc)
		return;
	while (argc--)
		free(argv[argc]);
}

int run_builtin(int argc, char **argv)
{
	for (int i = 0; i < builtins_count; i++)
	{
		if (strcmp(argv[0], builtins[i].name) == 0)
		{
			builtins[i].func(argc, argv);
			return 0;
		}
	}
	return -1;
}


int wait_for_child(pid_t child_pid)
{
	int status = 0;
	waitpid(child_pid, &status, 0);
	return status;
}
