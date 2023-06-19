/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:49:31 by asioud            #+#    #+#             */
/*   Updated: 2023/06/19 17:41:07 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SIGNALS_H
#define SIGNALS_H

#include "minishell.h"

void signals(struct termios *mirror_termios);
void save_settings_and_remove_c(struct termios *mirror_termios);
void signal_ctrl_c(void);
void signal_ctrl_backslash(void);
void handle_sigint(int sig_num);

#endif
