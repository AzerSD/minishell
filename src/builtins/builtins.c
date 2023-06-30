/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 05:41:31 by asioud            #+#    #+#             */
/*   Updated: 2023/06/30 23:45:12 by asioud           ###   ########.fr       */
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

	bt = my_malloc(&shell.memory, sizeof(t_builtin_info));
	if (bt == NULL)
	{
		return (NULL);
	}
	bt->builtins = builtins;
	bt->count = sizeof(builtins) / sizeof(struct s_builtin);
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
