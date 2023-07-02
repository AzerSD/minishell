/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:28:21 by asioud            #+#    #+#             */
/*   Updated: 2023/07/02 17:07:02 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_settings_and_remove_c(struct termios *mirror_termios)
{
	struct termios	termios_settings;

	tcgetattr(STDIN_FILENO, mirror_termios);
	tcgetattr(STDIN_FILENO, &termios_settings);
	termios_settings.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios_settings);
}

void	handle_sigint(int sig_num)
{
	if (sig_num == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// void	signal_ctrl_c(void) //SIGINT
// {
// 	struct sigaction ctrl_c;

// 	ctrl_c.sa_handler = handle_sigint;
// 	ctrl_c.sa_flags = SA_RESTART;
// 	sigemptyset(&ctrl_c.sa_mask);
// 	sigaction(SIGINT, &ctrl_c, NULL);
// }

// void	signal_ctrl_backslash(void) //SIGQUIT
// {
// 	struct sigaction ctrl_back_slash;

// 	ctrl_back_slash.sa_handler = SIG_IGN;
// 	ctrl_back_slash.sa_flags = SA_RESTART;
// 	sigemptyset(&ctrl_back_slash.sa_mask);
// 	sigaction(SIGQUIT, &ctrl_back_slash, NULL);
// }

// void	signal_ctrl_d(void) //SIGQUIT
// {
// 	struct sigaction ctrl_d;

// 	ctrl_d.sa_handler = SIG_IGN;
// 	ctrl_d.sa_flags = SA_RESTART;
// 	sigemptyset(&ctrl_d.sa_mask);
// 	sigaction(SIGQUIT, &ctrl_d, NULL);
// }

void	signals(struct termios *mirror_termios)
{
	save_settings_and_remove_c(mirror_termios);
	signal_ctrl_backslash();
	signal_ctrl_c();
	signal_ctrl_d();
}

// git add .
// git commit -m "dasfasdf"
// git push