/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 05:41:31 by asioud            #+#    #+#             */
/*   Updated: 2023/07/01 17:16:25 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_builtin	*init_builtins(void)
{
	static struct s_builtin	builtins[8];

	builtins[0].name = "dump";
	builtins[0].func = ft_dump;
	builtins[1].name = "echo";
	builtins[1].func = ft_echo;
	builtins[2].name = "env";
	builtins[2].func = ft_env;
	builtins[3].name = "pwd";
	builtins[3].func = ft_pwd;
	builtins[4].name = "cd";
	builtins[4].func = ft_cd;
	builtins[5].name = "export";
	builtins[5].func = ft_export;
	builtins[6].name = "unset";
	builtins[6].func = ft_unset;
	builtins[7].name = "exit";
	builtins[7].func = ft_exit;
	return (builtins);
}

t_builtin_info	*get_bt(void)
{
	t_builtin_info	*bt;

	bt = my_malloc(&shell.memory, sizeof(t_builtin_info));
	if (bt == NULL)
	{
		return (NULL);
	}
	bt->builtins = init_builtins();
	bt->count = 8;
	return (bt);
}

int	exec_builtin(int argc, char **argv)
{
	t_builtin_info	*bt;
	int				i;

	i = 0;
	bt = get_bt();
	if (argc < 1)
		return (-1);
	while (i < bt->count)
	{
		if (strcmp(argv[0], bt->builtins[i].name) == 0)
		{
			return (bt->builtins[i].func(argc, argv));
		}
		i++;
	}
	return (-9);
}
