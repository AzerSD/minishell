/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 01:55:30 by asioud            #+#    #+#             */
/*   Updated: 2023/06/16 23:01:19 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# define PS1 "$ "
# define PS2 "> "

# include "minishell.h"

void prompt_display_ps1(void);
void prompt_display_ps2(void);
int parse_and_execute(t_cli *cli);

#endif
