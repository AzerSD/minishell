/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:28:21 by asioud            #+#    #+#             */
/*   Updated: 2023/07/01 02:59:29 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This function is designed to handle terminal settings and is part of handling SIGINT signal
void	save_settings_and_remove_c(struct termios *mirror_termios)
{
	struct termios	termios_settings;

	// `struct termios` contains terminal I/O settings.
	// `tcgetattr()` gets the parameters associated with (in this case the standard input)
	//  we save the current terminal settings into the `mirror_termios`.
	tcgetattr(STDIN_FILENO, mirror_termios);
	//  this time we save  current settings of the terminal,
	// into `termios_settings`.
	tcgetattr(STDIN_FILENO, &termios_settings);
	// We modify `termios_settings` to disable echoing of control characters.
	// `ECHOCTL` is a flag that, when set, enables the echoing,
	// and "~ECHOCTL" creates a bitmask to turn it off.
	// &= operator applies this bitmask to the `c_lflag` field of
	// `termios_settings`, effectively turning off the `ECHOCTL` flag.
	termios_settings.c_lflag &= ~ECHOCTL;
	// sets the parameters associated with the terminal (referred by the file descriptor) from the termios structure.
	// `TCSAFLUSH` option makes the change occur after all output written to the file descriptor has been transmitted,
	// and all input that has been received but not read will be discarded before the change is made.
	// The modified `termios_settings` is applied to the terminal,
	// effectively disabling control character echoing.
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios_settings);
}

void	handle_sigint(int sig_num)
{
	if (sig_num == SIGINT)
	{
		// writing a newline to the standard output,
		write(STDOUT_FILENO, "\n", 1);
		/*This tells readline that the cursor is on a new line*/
		rl_on_new_line();
		/* replaces the contents of readline's line buffer with text.
		If clear_undo is non-zero, the undo list is cleared as well.*/
		rl_replace_line("", 0);
		/*This updates the screen to reflect the current state of the line being edited.*/
		rl_redisplay();
	}
}

void	signal_ctrl_c(void) //SIGINT
{
	struct sigaction ctrl_c;

	ctrl_c.sa_handler = handle_sigint;
	ctrl_c.sa_flags = SA_RESTART;
	sigemptyset(&ctrl_c.sa_mask);
	sigaction(SIGINT, &ctrl_c, NULL);
}

void	signal_ctrl_backslash(void) //SIGQUIT
{
	struct sigaction ctrl_back_slash;

	ctrl_back_slash.sa_handler = SIG_IGN;
	ctrl_back_slash.sa_flags = SA_RESTART;
	sigemptyset(&ctrl_back_slash.sa_mask);
	sigaction(SIGQUIT, &ctrl_back_slash, NULL);
}

void	signal_ctrl_d(void) //SIGQUIT
{
	struct sigaction ctrl_d;

	ctrl_d.sa_handler = SIG_IGN;
	ctrl_d.sa_flags = SA_RESTART;
	sigemptyset(&ctrl_d.sa_mask);
	sigaction(SIGQUIT, &ctrl_d, NULL);
}

void	signals(struct termios *mirror_termios)
{
	save_settings_and_remove_c(mirror_termios);
	signal_ctrl_backslash();
	signal_ctrl_c();
	signal_ctrl_d();
}

// `sigaction` is both a function and a structure in C:
// 1. `sigaction` as a function:
// This is a function used to change the action taken by a process on receipt of a specific signal.
//  int sigaction(int signum, const struct sigaction *act,
// struct sigaction *oldact);

//`signum` is the signal number,
// `act` is the new action to be set (NULL if no change is requested),
// and `oldact` is used to save the old action (NULL if not needed).

// 2. `sigaction` as a structure:
// This is a structure that specifies the new action to be taken for the signal. It is defined as:

//
// struct sigaction {
//     void     (*sa_handler)(int);// a pointer to the signal-handling function,
//     void     (*sa_sigaction)(int, siginfo_t *, void *);
//     sigset_t   sa_mask;
//the set of signals that should be blocked during execution of the signal handling function,
//     int        sa_flags; //options for signal handling
//     void     (*sa_restorer)(void);// obsolete and should not be used in new code.
// };

// struct termios {
// 	tcflag_t        c_iflag;        /* input flags */
// 	tcflag_t        c_oflag;        /* output flags */
// 	tcflag_t        c_cflag;        /* control flags */
// 	tcflag_t        c_lflag;        /* local flags */
// 	cc_t            c_cc[NCCS];     /* control chars */
// 	speed_t         c_ispeed;       /* input speed */
// 	speed_t         c_ospeed;       /* output speed */
// };
