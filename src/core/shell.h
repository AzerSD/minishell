/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 01:55:30 by asioud            #+#    #+#             */
/*   Updated: 2023/06/23 17:37:35 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# define PS1 "$ "
# define PS2 "> "


void	prompt_display_ps1(void);
void	prompt_display_ps2(void);
int		parse_and_execute(t_cli *cli);
void	print_ast(t_node *node, int indent);

#endif
