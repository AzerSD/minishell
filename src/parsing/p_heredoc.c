/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 01:12:36 by asioud            #+#    #+#             */
/*   Updated: 2023/07/03 20:35:30 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*new_redirection_node(t_token *tok, t_node *ptr)
{
	t_node	*redirection_node;

	redirection_node = new_node(NODE_HEREDOC);
	set_node_val_str(redirection_node, tok->text);
	if (!redirection_node)
	{
		free_node_tree(ptr);
		free_token(tok);
		return (NULL);
	}
	free_token(tok);
	return (redirection_node);
}

t_token	*check_token(t_cli *cli, t_curr_tok *curr, t_node *ptr)
{
	t_token	*tok;

	tok = get_token(cli, curr);
	if (tok == EOF_TOKEN)
	{
		free_node_tree(ptr);
		return (NULL);
	}
	return (tok);
}

int	create_temp_file(t_token *tok, t_node *ptr, char **tmp_file)
{
	int	tmp_fd;

	*tmp_file = ft_strjoin("/tmp/heredoc", ft_randstring(10));
	tmp_fd = open(*tmp_file, O_CREAT | O_RDWR | O_APPEND, 0777);
	if (tmp_fd == -1)
	{
		free_node_tree(ptr);
		free_token(tok);
		return (-1);
	}
	return (tmp_fd);
}

t_heredoc_data	*prepare_heredoc(t_token *tok, t_cli *cli, t_curr_tok *curr,
		t_node *ptr)
{
	t_heredoc_data	*data;

	srand(time(NULL));
	data = my_malloc(g_shell.memory, sizeof(t_heredoc_data));
	if (!data)
		return (NULL);
	data->redirection_node = new_redirection_node(tok, ptr);
	if (!data->redirection_node)
		return (NULL);
	data->tok = check_token(cli, curr, ptr);
	if (!data->tok)
		return (NULL);
	data->tmp_fd = create_temp_file(data->tok, ptr, &(data->tmp_file));
	if (data->tmp_fd == -1)
	{
		free_node_tree(ptr);
		free_token(data->tok);
		free(data->tmp_file);
		return (NULL);
	}
	return (data);
}

t_node	*execute_heredoc(t_heredoc_data *data, t_node *ptr)
{
	int		pipe_fd[2];
	pid_t	pid;
	t_node	*file_node;

	if (pipe(pipe_fd) < 0)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		handle_child_process(data->tmp_fd, pipe_fd);
	else
		handle_parent_process(pipe_fd, data->tok, data->tmp_fd);
	file_node = new_node(NODE_FILE);
	set_node_val_str(file_node, data->tmp_file);
	if (!file_node)
		return (free_node_tree(ptr), free_node_tree(ptr), NULL);
	add_child_node(data->redirection_node, file_node);
	return (add_child_node(ptr, data->redirection_node), ptr);
}
