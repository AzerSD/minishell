/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 02:34:11 by asioud            #+#    #+#             */
/*   Updated: 2023/07/03 20:22:52 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	create_first_child_process(int *pipefd, t_node *node)
{
	pid_t	child_pid1;

	child_pid1 = fork();
	if (child_pid1 == -1)
	{
		perror("fork");
		return (-1);
	}
	if (child_pid1 == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execc(node->first_child);
		exit(g_shell.status);
	}
	return (child_pid1);
}

pid_t	create_second_child_process(int *pipefd, t_node *node)
{
	pid_t	child_pid2;

	child_pid2 = fork();
	if (child_pid2 == -1)
	{
		perror("fork");
		return (-1);
	}
	if (child_pid2 == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		g_shell.status = execc(node->first_child->next_sibling);
		exit(g_shell.status);
	}
	return (child_pid2);
}

int	execute_pipeline(t_node *node)
{
	int		pipefd[2];
	int		status1;
	int		status2;
	pid_t	child_pid1;
	pid_t	child_pid2;

	status1 = 0;
	status2 = 0;
	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);
	child_pid1 = create_first_child_process(pipefd, node);
	if (child_pid1 == -1)
		return (1);
	child_pid2 = create_second_child_process(pipefd, node);
	if (child_pid2 == -1)
		return (1);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(child_pid1, &status1, 0);
	waitpid(child_pid2, &status2, 0);
	status1 = WEXITSTATUS(status1);
	status2 = WEXITSTATUS(status2);
	return (status2);
}
