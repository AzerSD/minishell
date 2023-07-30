/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 01:57:47 by asioud            #+#    #+#             */
/*   Updated: 2023/07/03 21:17:12 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(int argc, char **argv)
{
	char	*path;

	(void)argc;
	if (ft_strchr(argv[0], '/'))
		execv(argv[0], argv);
	else
	{
		path = search_path(argv[0]);
		if (!path)
			return (1);
		execv(path, argv);
	}
	return (0);
}

pid_t	fork_command(int argc, char **argv)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		exec_cmd(argc, argv);
		ft_printf_fd(STDERR_FILENO, "minishell: %s: command not found\n", \
			argv[0]);
		if (errno == ENOEXEC)
			exit(126);
		else if (errno == ENOENT)
			exit(127);
		else
			exit(0);
	}
	return (child_pid);
}

int	exec_child_process(int argc, char **argv)
{
	int		status;
	pid_t	child_pid;

	status = 0;
	child_pid = fork_command(argc, argv);
	if (child_pid == -1)
	{
		ft_printf_fd(STDERR_FILENO, "error: failed to fork command: %s\n", \
		strerror(errno));
		return (1);
	}
	waitpid(child_pid, &status, 0);
	status = WEXITSTATUS(status);
	g_shell.status = status;
	return (status);
}

void	init_vars(int *argc, int *targc, char ***argv, int *ret)
{
	*argc = 0;
	*targc = 0;
	*argv = NULL;
	*ret = 0;
}

int	execc(t_node *node)
{
	char	**argv;
	int		argc;
	int		targc;
	int		ret;
	int		pipeline_status;

	init_vars(&argc, &targc, &argv, &ret);
	if (node->type == NODE_ASSIGNMENT)
		return (string_to_symtab(node->first_child->val.str), 0);
	if (node->type == NODE_PIPE)
	{
		ret = dup(STDIN_FILENO);
		pipeline_status = execute_pipeline(node);
		dup2(ret, STDIN_FILENO);
		close(ret);
		g_shell.status = pipeline_status;
		return (pipeline_status);
	}
	parse_ast(node, &argc, &targc, &argv);
	if (setup_redirections(node))
		return (1);
	ret = exec_builtin(argc, argv);
	if (ret >= 0)
		return (g_shell.status = ret, ret);
	return (exec_child_process(argc, argv));
}
