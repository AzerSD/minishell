/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 01:57:47 by asioud            #+#    #+#             */
/*   Updated: 2023/06/24 02:46:25 by asioud           ###   ########.fr       */
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
    return (errno == ENOEXEC ? 126 : errno == ENOENT ? 127 : EXIT_FAILURE);
}

pid_t fork_command(int argc, char **argv, t_node *node)
{
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == 0)
    {
        if (setup_redirections(node) != 0)
            exit(EXIT_FAILURE);
        else
		{
			if (exec_builtin(argc, argv) != 0)
			{
				exec_cmd(argc, argv);
				fprintf(stderr, "minishell: %s: command not found\n", argv[0]);
			}
		}
		if (errno == ENOEXEC)
			exit(126);
		else if (errno == ENOENT)
			exit(127);
		else
			exit(EXIT_FAILURE);
    }
    return (child_pid);
}

int	parse_ast(t_node *node, int *argc, int *targc, char ***argv)
{
	struct s_word	*w;
	struct s_word	*w2;
	t_node			*child;
	char			*str;
	char			*arg;

	child = node->first_child;
	while (child)
	{
		str = child->val.str;
		if (child->type == NODE_INPUT || child->type == NODE_OUTPUT
			|| child->type == NODE_APPEND || child->type == NODE_HEREDOC)
			break ;
		w = expand(str);
		if (!w)
		{
			child = child->next_sibling;
			continue ;
		}
		w2 = w;
		while (w2)
		{
			if (check_buffer_bounds(argc, targc, argv))
			{
				arg = my_malloc(&shell.memory, strlen(w2->data) + 1);
				if (arg)
				{
					strcpy(arg, w2->data);
					(*argv)[(*argc)++] = arg;
				}
			}
			w2 = w2->next;
		}
		free_all_words(w);
		child = child->next_sibling;
	}
	if (check_buffer_bounds(argc, targc, argv))
		(*argv)[(*argc)] = NULL;
	return (0);
}

int	execc(t_node *node)
{
	char **argv = NULL;
	int argc = 0;
	int targc = 0;
	pid_t child_pid;
	int status;

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

		return (pipeline_status);
	}

	if (parse_ast(node, &argc, &targc, &argv) != 0 || !node)
		return (1);

	child_pid = fork_command(argc, argv, node);

	if (child_pid == -1)
	{
		fprintf(stderr, "error: failed to fork command: %s\n", strerror(errno));
		free_argv(argc, argv);
		return (1);
	}

	waitpid(child_pid, &status, 0);
	shell.status = WEXITSTATUS(status);
    return shell.status;
}