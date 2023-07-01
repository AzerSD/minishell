/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:49:31 by asioud            #+#    #+#             */
/*   Updated: 2023/07/01 16:28:54 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

void	signal_ctrl_backslash(void);
void	signal_ctrl_d(void);
void	signal_ctrl_c(void);
void	signals(struct termios *mirror_termios);
void	save_settings_and_remove_c(struct termios *mirror_termios);
void	handle_sigint(int sig_num);

#endif
