/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 05:41:31 by asioud            #+#    #+#             */
/*   Updated: 2023/06/19 18:21:07 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 
#include "minishell.h"

struct s_builtin builtins[] =
{
    { "dump"    , ft_dump },
    { "echo"    , ft_echo },
    { "env"     , ft_env },
    { "pwd"     , ft_pwd },
    { "cd"      , ft_cd },
    { "export"  , ft_export },
    { "unset"   , ft_unset },
    { "exit"    , ft_exit },
};

t_builtin_info *get_bt()
{
    t_builtin_info *bt = malloc(sizeof(t_builtin_info));
    if (bt == NULL) {
        return NULL; // handle error as needed
    }
    bt->builtins = builtins;
    bt->count = sizeof(builtins) / sizeof(struct s_builtin);
    return bt;
}

int is_builtin(int argc, char **argv, t_builtin_info *bt)
{
    for (int i = 0; i < bt->count; i++)
    {
        if (strcmp(argv[0], bt->builtins[i].name) == 0)
        {
            bt->builtins[i].func(argc, argv);
            return 0;
        }
    }
    return -1;
}

