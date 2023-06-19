/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 02:34:11 by asioud            #+#    #+#             */
/*   Updated: 2023/06/19 03:28:48 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int execute_pipeline(int argc, char **argv, t_node *node)
{
    int pipefd[2];
	pid_t child_pid;
	
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return 1;
    }

    child_pid = fork();
    if (child_pid == -1)
    {
        perror("fork");
        return 1;
    }

if (child_pid == 0)
{
    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);
    execc(node->first_child);
    exit(EXIT_FAILURE);
}

    close(pipefd[1]);
    wait_for_child(child_pid);
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);

    int status = execc(node->first_child->next_sibling);
    return status;
}
