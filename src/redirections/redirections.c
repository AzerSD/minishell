/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:04:09 by lhasmi            #+#    #+#             */
/*   Updated: 2023/06/08 11:09:23 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//  Redirection is a feature in Linux such that when executing a command, you can
// change the standard input/output devices. The basic workflow for coding
// redirections is:
// first parse the command input for the <, >, <<, >> redir symbols
// and then use the dup2() function to redirect the STDIN, STDOUT, and STDERR
//  file descriptors as needed.

void redirections (int argc, char *argv[])
{
	
}