/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:49:31 by asioud            #+#    #+#             */
/*   Updated: 2023/04/28 23:15:35 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

// #define SIGHUP  1   /* Hangup the process */		/* when term closed */     
// #define SIGINT  2   /* Interrupt the process */     /* ctrl + c */
#define SIGQUIT 3   /* Quit the process */			/* ctrl + \ */
// #define SIGILL  4   /* Illegal instruction. */		/* invalid instruction */
// #define SIGTRAP 5   /* Trace trap. */				/* debugger */
// #define SIGABRT 6   /* Abort. */					/* ctrl + d */


void   sigint_handler(int sig);
void   handle_sigquit(int sig);

#endif