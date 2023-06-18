/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:04:09 by lhasmi            #+#    #+#             */
/*   Updated: 2023/06/18 02:29:02 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int setup_redirections(t_node *node)
{
    int fd;
    int flags = 0;
    int std_fd = -1;
    t_node *child = node->first_child;

    while (child)
    {
        if (child->type == NODE_INPUT || child->type == NODE_OUTPUT || child->type == NODE_APPEND || child->type == NODE_HEREDOC)
        {


            if (child->type == NODE_INPUT)
            {
                flags = O_RDONLY;
                std_fd = STDIN_FILENO;
            }
            else if (child->type == NODE_OUTPUT)
            {
                flags = O_WRONLY | O_CREAT | O_TRUNC;
                std_fd = STDOUT_FILENO;
            }
            else if (child->type == NODE_APPEND)
            {
                flags = O_WRONLY | O_CREAT | O_APPEND;
                std_fd = STDOUT_FILENO;
            }
 
            if (child->first_child && child->first_child->val.str)
            {
                fd = open(child->first_child->val.str, flags, 0644);
                if (fd == -1)
                {
                    perror("open");
                    return 1;
                }

                if (dup2(fd, std_fd) == -1)
                {
                    perror("dup2");
                    close(fd);
                    return 1;
                }

                close(fd);
            }
        }
        child = child->next_sibling;
    }

    return 0;
}
