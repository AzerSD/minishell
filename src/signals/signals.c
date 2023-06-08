/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:28:21 by asioud            #+#    #+#             */
/*   Updated: 2023/06/08 11:13:00 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// A signal is a software interrupt delivered to a process. 
// OS uses signals to report exceptional situations to an executing program. 
// Some signals, like SIGINT and SIGSTOP, can be sent by the user to a running 
// program (via ctrl-C and ctrl-Z). For these, you'll need to set up signal handlers 
// using the signal() or sigaction() system calls to specify how your shell should 
// respond to these signals.

#include<signal.h>

#include "../core/shell.h"
#include "signals.h"

void   handle_sigquit(int sig)
{
    (void)sig;
}


