/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 01:57:59 by asioud            #+#    #+#             */
/*   Updated: 2023/05/04 05:09:14 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "../parsing/node.h"

/**
 * @brief Searches for a file in the system's `PATH` environment variable.
 * If an error occurs, it sets the `errno` variable and returns NULL.
 * @param file The name of the file to search for.
 * @return The full path to the file if found, or NULL if not found.
*/
char *search_path(char *file);

/**
 * @brief Executes a command with the given argument count and argument list. 
 * @param argc Number of arguments in argv.
 * @param argv The command and its arguments.
 * @return int 0 on success, 1 on failure.
 */
int exec_cmd(int argc, char **argv);

/**
 * @brief  Handle the execution of simple commands by creating an 
 * argument list (argv) from the nodes in the AST, checking for built-in
 * commands, and then forking a new process to execute external commands.
 * @param node The AST node representing the command to be executed.
 * @return 1 on success, 0 on failure.
 */
int execc(t_node *node);

char *search_path(char *file);

#endif
