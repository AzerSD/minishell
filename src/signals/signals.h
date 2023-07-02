/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:49:31 by asioud            #+#    #+#             */
/*   Updated: 2023/07/02 14:21:33 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

void	signals(struct termios *mirror_termios);
void	save_settings_and_remove_c(struct termios *mirror_termios);
void	signal_ctrl_backslash(void);
void	handle_sigint(int sig_num);
void	signal_ctrl_c(void);
void	signal_ctrl_d(void);
#endif
