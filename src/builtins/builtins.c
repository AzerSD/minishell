/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 05:41:31 by asioud            #+#    #+#             */
/*   Updated: 2023/07/27 15:42:47 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_builtin	builtins[] = {
{"dump", ft_dump},
{"echo", ft_echo},
{"env", ft_env},
{"pwd", ft_pwd},
{"cd", ft_cd},
{"export", ft_export},
{"unset", ft_unset},
{"exit", ft_exit},
};

t_builtin_info	*get_bt(void)
{
	t_builtin_info	*bt;

	bt = malloc(sizeof(t_builtin_info));
	if (bt == NULL)
	{
		return (NULL);
	}
	bt->builtins = builtins;
	bt->count = sizeof(builtins) / sizeof(struct s_builtin);
	return (bt);
}

int	is_builtin(int argc, char **argv, t_builtin_info *bt)
{
	int	i;

	i = 0;
	while (i < bt->count)
	{
		if (strcmp(argv[0], bt->builtins[i].name) == 0)
		{
			bt->builtins[i].func(argc, argv);
			return (0);
		}
		i++;
	}
	return (-1);
}
