/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:49:31 by asioud            #+#    #+#             */
/*   Updated: 2023/06/09 15:28:50 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SIGNALS_H
#define SIGNALS_H

#include <termios.h>  // for struct termios
#include <signal.h>   // for struct sigaction, sigemptyset, sigaction
#include <unistd.h>
#include <readline/readline.h>

// Global variable to track SIGINT
extern int g_ctrl_c;

// Function prototypes
void signals(struct termios *mirror_termios);
void save_settings_and_remove_c(struct termios *mirror_termios);
void signal_ctrl_c(void);
void signal_ctrl_backslash(void);
void handle_sigint(int sig_num);

#endif
