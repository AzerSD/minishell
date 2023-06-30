/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:04:09 by lhasmi            #+#    #+#             */
/*   Updated: 2023/06/30 18:06:46 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Set the up redirections object
 * if there's a redirection node,
	open the file and redirect the file descriptor to the temporary file. 
 * @param node 
 * @return int 
 */
int	setup_redirections(t_node *node)
{
	t_node			*child;
	int				fd;
	int				flags;
	int				std_fd;
	int				std_fd_err;
	struct s_word	*w;

	child = node->first_child;
	while (child)
	{
		if (child->type == NODE_INPUT || child->type == NODE_OUTPUT
			|| child->type == NODE_APPEND || child->type == NODE_HEREDOC)
		{
			flags = 0;
			std_fd = -1;
			std_fd_err = -1;
			if (child->type == NODE_INPUT)
			{
				flags = O_RDONLY;
				std_fd = STDIN_FILENO;
			}
			else if (child->type == NODE_OUTPUT)
			{
				flags = O_WRONLY | O_CREAT | O_TRUNC;
				std_fd = STDOUT_FILENO;
				std_fd_err = STDERR_FILENO;
			}
			else if (child->type == NODE_APPEND)
			{
				flags = O_WRONLY | O_CREAT | O_APPEND;
				std_fd = STDOUT_FILENO;
				std_fd_err = STDERR_FILENO;
			}
			else if (child->type == NODE_HEREDOC)
			{
				flags = O_RDONLY;
				std_fd = STDIN_FILENO;
			}
			else
			{
				return (1);
			}
			if (child->first_child && child->first_child->val.str)
			{
				w = make_word(child->first_child->val.str);
				remove_quotes(w);
				fd = open(w->data, flags, 0644);
				if (fd == -1)
				{
					perror("open");
					return (1);
				}
				if (dup2(fd, std_fd) == -1)
				{
					perror("dup2");
					close(fd);
					return (1);
				}
				if (std_fd_err == STDERR_FILENO)
					if (dup2(fd, std_fd_err) == -1)
					{
						perror("dup2");
						close(fd);
						return (1);
					}
				close(fd);
			}
		}
		child = child->next_sibling;
	}
	return (0);
}
