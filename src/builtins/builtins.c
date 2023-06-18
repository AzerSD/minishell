/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 05:41:31 by asioud            #+#    #+#             */
/*   Updated: 2023/06/18 19:13:27 by lhasmi           ###   ########.fr       */
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

int					builtins_count = sizeof(builtins)
	/ sizeof(struct s_builtin);
