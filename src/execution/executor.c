/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 01:57:47 by asioud            #+#    #+#             */
/*   Updated: 2023/07/01 02:58:38 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(int argc, char **argv)
{
	char	*path;

	(void)argc;
	if (strchr(argv[0], '/'))
		execv(argv[0], argv);
	else
	{
		path = search_path(argv[0]);
		if (!path)
			return (1);
		execv(path, argv);
		free(path);
	}
	return (0);
}

pid_t	fork_command(int argc, char **argv, t_node *node)
{
	pid_t	child_pid;
	int		builtin_status;

	child_pid = fork();
	if (child_pid == 0)
	{
		exec_cmd(argc, argv);
		fprintf(stderr, "minishell: %s: command not found\n", argv[0]);
		if (errno == ENOEXEC)
			exit(126);
		else if (errno == ENOENT)
			exit(127);
		else
			exit(0);
	}
	return (child_pid);
}

struct s_word	*get_node_content(t_node **child)
{
	struct s_word	*w;
	char			*str;

	if ((*child)->type == NODE_INPUT || (*child)->type == NODE_OUTPUT
		|| (*child)->type == NODE_APPEND || (*child)->type == NODE_HEREDOC)
	{
		*child = (*child)->next_sibling;
		return (NULL);
	}
	str = (*child)->val.str;
	w = expand(str);
	if (!w)
		return (NULL);
	return (w);
}

void	parse_ast(t_node *node, int *argc, int *targc, char ***argv)
{
	struct s_word	*w;
	t_node			*child;
	char			*arg;

	child = node->first_child;
	while (child)
	{
		w = get_node_content(&child);
		if (!w)
			continue ;
		while (w)
		{
			if (check_buffer_bounds(argc, targc, argv))
			{
				arg = my_malloc(&shell.memory, strlen(w->data) + 1);
				if (arg)
				{
					strcpy(arg, w->data);
					(*argv)[(*argc)++] = arg;
				}
			}
			w = w->next;
		}
		child = child->next_sibling;
	}
	if (check_buffer_bounds(argc, targc, argv))
		(*argv)[(*argc)] = NULL;
}

int	execc(t_node *node)
{
	char	**argv = NULL;
	int		argc = 0;
	int		targc = 0;
	pid_t	child_pid;
	int		status = 0;
	int		ret = 0;

	if (!node)
		return (1);

	if (node->type == NODE_ASSIGNMENT)
	{
		string_to_symtab(node->first_child->val.str);
		return (0);
	}

	if (node->type == NODE_PIPE)
	{
		int original_stdin = dup(STDIN_FILENO);
		int pipeline_status = execute_pipeline(argc, argv, node);
		dup2(original_stdin, STDIN_FILENO);
		close(original_stdin);
		shell.status = pipeline_status;
		return (pipeline_status);
	}

	parse_ast(node, &argc, &targc, &argv);

	if (setup_redirections(node))
		return (1);
	ret = exec_builtin(argc, argv);
	if (ret >= 0)
	{
		shell.status = ret;
		return (ret);
	}
	child_pid = fork_command(argc, argv, node);
	if (child_pid == -1)
	{
		fprintf(stderr, "error: failed to fork command: %s\n", strerror(errno));
		free_argv(argc, argv);
		return (1);
	}

	waitpid(child_pid, &status, 0);
	status = WEXITSTATUS(status);
	shell.status = status;
	return (status);
}