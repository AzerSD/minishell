/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 02:34:11 by asioud            #+#    #+#             */
/*   Updated: 2023/06/24 01:21:32 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_pipeline(int argc, char **argv, t_node *node)
{
    int pipefd[2];
    pid_t child_pid;
    int status;

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
        execvp(argv[0], argv);
        exit(EXIT_FAILURE);
    }

    close(pipefd[1]);

    char buffer[4096];
    ssize_t bytesRead;
    while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer))) > 0)
    {
        write(STDOUT_FILENO, buffer, bytesRead);
    }

    close(pipefd[0]);

    waitpid(child_pid, &status, 0);
    shell.status = WEXITSTATUS(status);

    int pipeline_status = execc(node->first_child->next_sibling);
    shell.status = pipeline_status;
    return pipeline_status;
}
