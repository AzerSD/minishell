/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 01:57:47 by asioud            #+#    #+#             */
/*   Updated: 2023/06/18 14:21:37 by lhasmi           ###   ########.fr       */
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

void	resolve_env_vars(char **argv)
{
	char	*env_var;

	for (int i = 0; argv[i] != NULL; i++)
	{
		if (argv[i][0] == '$')
		{
			env_var = getenv(argv[i] + 1);
			if (env_var != NULL)
			{
				argv[i] = env_var;
			}
		}
	}
}

pid_t	fork_command(int argc, char **argv, t_node *node)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		resolve_env_vars(argv);
		if (setup_redirections(node) == 0)
		{
			exec_cmd(argc, argv);
		}
		fprintf(stderr, "minishell: %s: command not found\n", argv[0]);
		if (errno == ENOEXEC)
			exit(126);
		else if (errno == ENOENT)
			exit(127);
		else
			exit(EXIT_FAILURE);
	}
	// else
    // {
    //     // This is the parent process
    //     waitpid(child_pid, &status, 0); // Wait for the child process to terminate
    //     if (WIFEXITED(status)) // If the child terminated normally
    //     {
    //         exec_status = WEXITSTATUS(status); // Get the exit status of the child
    //     }
    // }
	return (child_pid);
}

int	parse_arguments(t_node *node, int *argc, int *targc, char ***argv)
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
				arg = malloc(strlen(w2->data) + 1);
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
	char	**argv;
	int		argc;
	int		targc;
	pid_t	child_pid;
	int		status;
	int		original_stdin;
	int		pipeline_status;

	argv = NULL;
	argc = 0;
	targc = 0;
	if (!node)
		return (1);
	if (node->type == NODE_ASSIGNMENT)
	{
		string_to_symtab(node->first_child->val.str);
		return (0);
	}
	if (node->type == NODE_PIPE)
	{
		original_stdin = dup(STDIN_FILENO);
		pipeline_status = execute_pipeline(node);
		dup2(original_stdin, STDIN_FILENO);
		close(original_stdin);
		return (pipeline_status);
	}
	if (parse_arguments(node, &argc, &targc, &argv) != 0 || !node)
		return (1);
	if (setup_redirections(node) != 0)
	{
		free_argv(argc, argv);
		return (1);
	}
	if (run_builtin(argc, argv) == 0)
	{
		free_argv(argc, argv);
		return (0);
	}
	child_pid = fork_command(argc, argv, node);
	if (child_pid == -1)
	{
		fprintf(stderr, "error: failed to fork command: %s\n", strerror(errno));
		free_argv(argc, argv);
		return (1);
	}
	status = wait_for_child(child_pid);
	free_argv(argc, argv);
	return (status == 0 ? 0 : 1);
}
