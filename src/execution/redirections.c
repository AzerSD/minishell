/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:04:09 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/03 21:08:48 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_node_types(t_node *child, int *flags, int *std_fd,
		int *std_fd_err)
{
	if (child->type == NODE_INPUT)
	{
		*flags = O_RDONLY;
		*std_fd = STDIN_FILENO;
	}
	else if (child->type == NODE_OUTPUT)
	{
		*flags = O_WRONLY | O_CREAT | O_TRUNC;
		*std_fd = STDOUT_FILENO;
		*std_fd_err = STDERR_FILENO;
	}
	else if (child->type == NODE_APPEND)
	{
		*flags = O_WRONLY | O_CREAT | O_APPEND;
		*std_fd = STDOUT_FILENO;
		*std_fd_err = STDERR_FILENO;
	}
	else if (child->type == NODE_HEREDOC)
	{
		*flags = O_RDONLY;
		*std_fd = STDIN_FILENO;
	}
}

int	open_and_redirect(t_node *child, int flags, int std_fd, int std_fd_err)
{
	int				fd;
	struct s_word	*w;

	if (child->first_child && child->first_child->val.str)
	{
		w = make_word(child->first_child->val.str);
		remove_quotes(w);
		fd = open(w->data, flags, 0644);
		if (fd == -1)
			return (perror("open"), 1);
		if (dup2(fd, std_fd) == -1)
			return (perror("dup2"), close(fd), 1);
		if (std_fd_err == STDERR_FILENO)
		{
			if (dup2(fd, std_fd_err) == -1)
				return (perror("dup2"), close(fd), 1);
		}
		close(fd);
	}
	return (0);
}

int	setup_redirections(t_node *node)
{
	t_node	*child;
	int		flags;
	int		std_fd;
	int		std_fd_err;
	int		res;

	child = node->first_child;
	while (child)
	{
		if (child->type == NODE_INPUT || child->type == NODE_OUTPUT
			|| child->type == NODE_APPEND || child->type == NODE_HEREDOC)
		{
			flags = 0;
			std_fd = -1;
			std_fd_err = -1;
			handle_node_types(child, &flags, &std_fd, &std_fd_err);
			res = open_and_redirect(child, flags, std_fd, std_fd_err);
			if (res)
				return (1);
		}
		child = child->next_sibling;
	}
	return (0);
}

		// int saved_stdin = dup(STDIN_FILENO);
		// int saved_stdout = dup(STDOUT_FILENO);
		// int saved_stderr = dup(STDERR_FILENO);
		// dup2(saved_stdin, STDIN_FILENO);
		// dup2(saved_stdout, STDOUT_FILENO);
		// dup2(saved_stderr, STDERR_FILENO);
		// close(saved_stdin);
		// close(saved_stdout);
		// close(saved_stderr);