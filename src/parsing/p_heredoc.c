/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 01:12:36 by asioud            #+#    #+#             */
/*   Updated: 2023/07/03 03:54:44 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *randstring(size_t length) {

    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";        
    char *randomString = NULL;

    if (length) {
        randomString = malloc(sizeof(char) * (length +1));

        if (randomString) {            
            for (int n = 0;n < length;n++) {            
                int key = rand() % (int)(sizeof(charset) -1);
                randomString[n] = charset[key];
            }

            randomString[length] = '\0';
        }
    }

    return randomString;
}

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
	int		tmp_fd;

    *tmp_file = ft_strjoin("/tmp/heredoc", randstring(10));
	tmp_fd = open(*tmp_file, O_CREAT | O_RDWR | O_APPEND, 0777);
	if (tmp_fd == -1)
	{
        free_node_tree(ptr);
        free_token(tok);
		return (-1);
	}
	return (tmp_fd);
}

void	handle_child_process(int tmp_fd, int *pipe_fd)
{
	char	buffer[4096];
	ssize_t	bytes_read;

	close(pipe_fd[1]);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);

	while ((bytes_read = read(pipe_fd[0], buffer, sizeof(buffer) - 1)) > 0)
	{
		buffer[bytes_read] = '\0';
		write(tmp_fd, buffer, bytes_read);
	}
    close(tmp_fd);
	exit(EXIT_SUCCESS);
}

void	handle_parent_process(int *pipe_fd, t_token *tok, int tmp_fd)
{
	struct s_word	*w;
	char			*content;
	int				expanding;
    char           *line;

	close(pipe_fd[0]);
	w = NULL;
	expanding = 1;
	if (getncount(tok->text, '\'') >= 2 || getncount(tok->text, '\"') >= 2)
	{
		w = make_word(tok->text);
		expanding = 0;
		remove_quotes(w);
		tok->text = w->data;
		free(w);
		w = NULL;
	}
	line = get_next_line(fileno(stdin));
	{
		if (strchr(line, '$') && expanding)
			w = expand(line);
		if (w)
			content = w->data;
		else
			content = line;
	}
	while (content && (ft_strncmp(content, tok->text, ft_strlen(content) - 1) != 0))
	{
		write(pipe_fd[1], content, strlen(content));
		line = get_next_line(fileno(stdin));
		if (strchr(line, '$') && expanding)
			w = expand(line);
		if (w)
			content = w->data;
		else
			content = line;
		w = NULL;
	}
	close(pipe_fd[1]);
	wait(NULL);
    close(tmp_fd);
}

t_node	*p_heredoc(t_token *tok, t_cli *cli, t_curr_tok *curr, t_node *ptr)
{
	t_node	*redirection_node;
	int		tmp_fd;
	pid_t   pid;
	int     pipe_fd[2];
	t_node  *file_node;
    char    *tmp_file;

    srand(time(NULL));
	redirection_node = new_redirection_node(tok, ptr);
	if (!redirection_node)
		return (NULL);
	tok = check_token(cli, curr, ptr);
	if (!tok)
		return (NULL);
	tmp_fd = create_temp_file(tok, ptr, &tmp_file);
	if (tmp_fd == -1)
    {
        free_node_tree(ptr);
        free_token(tok);
        free(tmp_file);    
		return (NULL);
    }

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
		handle_child_process(tmp_fd, pipe_fd);
	else
		handle_parent_process(pipe_fd, tok, tmp_fd);
	free_token(tok);
	file_node = new_node(NODE_FILE);
	set_node_val_str(file_node, tmp_file);
    free(tmp_file);
	if (!file_node)
	{
		free_node_tree(ptr);
		return (NULL);
	}
	add_child_node(redirection_node, file_node);
	add_child_node(ptr, redirection_node);
	return (ptr);
}




// t_node *p_heredoc(t_token *tok, t_cli *cli, t_curr_tok *curr, t_node *ptr)
// {
//     t_node *redirection_node = new_node(NODE_HEREDOC);
//     set_node_val_str(redirection_node, tok->text);

//     if (!redirection_node) {
//         free_node_tree(ptr);
//         free_token(tok);
//         return NULL;
//     }

//     free_token(tok);
//     tok = get_token(cli, curr);
//     if (tok == EOF_TOKEN) {
//         free_node_tree(ptr);
//         return NULL;
//     }

//     char tmp_filename[] = "/tmp/heredocXXXXXX";


//     int tmp_fd = mkstemp(tmp_filename);
//     if (tmp_fd == -1) {
//         free_node_tree(ptr);
//         free_token(tok);
//         return NULL;
//     }

//     char *line = NULL;

//         pid_t pid;
//         int pipe_fd[2];

//         if (pipe(pipe_fd) < 0) {
//             perror("pipe");
//             exit(EXIT_FAILURE);
//         }

//         pid = fork();
//         if (pid < 0) {
//             perror("fork");
//             exit(EXIT_FAILURE);
//         }
//         else if (pid == 0) {
//             close(pipe_fd[1]); // Close the write end of the pipe in the child

//             char buffer[4096];
//             ssize_t bytes_read;
            
//             signal(SIGINT, SIG_DFL);
//             signal(SIGQUIT, SIG_DFL);

//             // Read from the pipe and write to the temp file
//             while ((bytes_read = read(pipe_fd[0], buffer, sizeof(buffer) - 1)) > 0) {
//                 buffer[bytes_read] = '\0';
//                 write(tmp_fd, buffer, bytes_read);
//             }

//             exit(EXIT_SUCCESS);
//         } 
//         else {
//             close(pipe_fd[0]); // Close the read end of the pipe in the parent

// 			struct s_word *w = NULL;
// 			char * content;
// 			int expanding = 1;
			
// 			if (getncount(tok->text, '\'') >= 2 || getncount(tok->text, '\"') >= 2)
// 			{
// 				w = make_word(tok->text);
// 				expanding = 0;
// 				remove_quotes(w);
// 				tok->text = w->data;
// 				free(w);
// 				w = NULL;
// 			}
			
//             line = get_next_line(fileno(stdin));
// 			{
// 				if (strchr(line, '$') && expanding)
// 					w = expand(line);
// 				if (w)
// 					content = w->data;
// 				else
// 					content = line;
// 			}
//             while (content && (ft_strncmp(content, tok->text, ft_strlen(content) - 1) != 0 ))
// 			{
//                 write(pipe_fd[1], content, strlen(content));
//                 line = get_next_line(fileno(stdin));
// 				if (strchr(line, '$') && expanding)
// 					w = expand(line);
// 				if (w)
// 					content = w->data;
// 				else
// 					content = line;
// 				w = NULL;
// 				// printf("strlentok %zu\n", ft_strlen(content));
//             }
//             close(pipe_fd[1]); // Close the write end of the pipe after done writing
//             wait(NULL);
//         }
//         free_token(tok);
//         t_node *file_node = new_node(NODE_FILE);
//         set_node_val_str(file_node, tmp_filename);
//         if (!file_node) {
//             free_node_tree(ptr);
//             return NULL;
//         }
//         add_child_node(redirection_node, file_node);
//         add_child_node(ptr, redirection_node);

//     return ptr;
// }