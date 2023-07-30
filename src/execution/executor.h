/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 01:57:59 by asioud            #+#    #+#             */
/*   Updated: 2023/07/03 04:33:22 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

/**
 * @brief Searches for a file in the system's `PATH` environment variable.
 * If an error occurs, it sets the `errno` variable and returns NULL.
 * @param file The name of the file to search for.
 * @return The full path to the file if found, or NULL if not found.
*/
char	*search_path(char *file);

/**
 * @brief Executes a command with the given argument count and argument list. 
 * @param argc Number of arguments in argv.
 * @param argv The command and its arguments.
 * @return int 0 on success, 1 on failure.
 */
int		exec_cmd(int argc, char **argv);

/**
 * @brief  Handle the execution of simple commands by creating an 
 * argument list (argv) from the nodes in the AST, checking for built-in
 * commands, and then forking a new process to execute external commands.
 * @param node The AST node representing the command to be executed.
 * @return 1 on success, 0 on failure.
 */
int		execc(t_node *node);

char	*search_path(char *file);

/**
 * @brief Frees the memory allocated for the given arguments.
 * @param argc The number of arguments.
 * @param argv null-terminated strings containing the arguments.
*/
void	free_argv(int argc, char **argv);

int		execute_pipeline(t_node *node);

/**
 * @brief Executes a command represented by a node tree.
 * @param node A pointer to a t_node struct representing the command node.
 * @return 0 on success, or 1 if an error occurs.
 *
 * This function parses the arguments from the node tree, checks for built-in
 * commands, and forks the current process to execute the command. It waits for
 * the child process to terminate and returns its status.
*/
int		execc(t_node *node);

/**
 * @brief Parses the command arguments from a node tree and stores them in an
 * 		array of strings.
 * @param node A pointer to a t_node struct representing the command node.
 * @param argc To store the number of arguments.
 * @param targc To Store the Total number of arguments.
 * @param argv A null-terminated strings that will store the arguments.
 * @return 0 on success, or a non-zero value if an error occurs.
*/
void	parse_ast(t_node *node, int *argc, int *targc, char ***argv);

/**
 * @brief Executes a command with the given arguments.
 * @param argc The number of arguments, including the command itself.
 * @param argv The first element is the command and the rest are the arguments.
 * @return 0 on success, or 1 if an error occurs.
*/
int		exec_cmd(int argc, char **argv);

/**
 * @brief Forks the current process and executes the given command in the
 * 		child process.
 * @param argc The number of arguments, including the command itself.
 * @param argv A null-terminated strings, where the first element is the command
 * 			and the rest are its arguments.
 * @return The process ID of the child process on success,
 * 		or -1 if an error occurs.
*/
pid_t	fork_command(int argc, char **argv);

////////////////////////////////////////////////////////////////////
//                          Redirections                          //
////////////////////////////////////////////////////////////////////

/**
 * @brief Redirects the standard input and output of the current process.
 * @param node The AST node representing the command to be executed.
 * @return 0 on success, 1 on failure.
*/
int		setup_redirections(t_node *node);

#endif
