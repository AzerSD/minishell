/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 02:34:11 by asioud            #+#    #+#             */
/*   Updated: 2023/08/18 19:46:41 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int execute_pipeline(int argc, char **argv, t_node *node)
int execute_pipeline(t_node *node)
{
    int pipefd[2];
    pid_t child_pid1, child_pid2;
    int status1 = 0, status2 = 0;

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return 1;
    }

    child_pid1 = fork();
    if (child_pid1 == -1)
    {
        perror("fork");
        return 1;
    }

    if (child_pid1 == 0)
    {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        status1 = execc(node->first_child);
        exit(shell.status);
    }

    child_pid2 = fork();
    if (child_pid2 == -1)
    {
        perror("fork");
        return 1;
    }

    if (child_pid2 == 0)
    {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        shell.status = execc(node->first_child->next_sibling);
        exit (shell.status);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(child_pid1, &status1, 0);
    waitpid(child_pid2, &status2, 0);

    status1 = WEXITSTATUS(status1);
    status2 = WEXITSTATUS(status2);
    return status2;
}
