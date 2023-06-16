/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:49:31 by asioud            #+#    #+#             */
/*   Updated: 2023/06/16 22:47:55 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SIGNALS_H
#define SIGNALS_H

#include "minishell.h"

// Global variable to track SIGINT
extern int g_ctrl_c;

// Function prototypes
void signals(struct termios *mirror_termios);
void save_settings_and_remove_c(struct termios *mirror_termios);
void signal_ctrl_c(void);
void signal_ctrl_backslash(void);
void handle_sigint(int sig_num);

#endif
