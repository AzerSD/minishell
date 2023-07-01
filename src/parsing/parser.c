/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 01:58:16 by asioud            #+#    #+#             */
/*   Updated: 2023/07/01 19:05:52 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

enum e_node_type get_node_type(e_token_type state)
{
	if (state == PARSE_DEFAULT)
		return NODE_COMMAND;
	else if (state == PARSE_ASSIGNMENT)
		return NODE_ASSIGNMENT;
	else if (state == TOKEN_PIPE)
		return NODE_PIPE;
    else if (state == TOKEN_OUTPUT)
        return NODE_OUTPUT;
    else if (state == TOKEN_INPUT)
        return NODE_INPUT;
    else if (state == TOKEN_APPEND)
        return NODE_APPEND;
    else if (state == TOKEN_HEREDOC)
        return NODE_HEREDOC;
	else
		return NODE_VAR;
}

t_node *p_pipe(t_node **ptr, t_node **parent, int *first_pipe) {
    t_node *null_node;
    if (*first_pipe)
        *ptr = *parent;

    *parent = new_node(NODE_PIPE);
    (*parent)->val.str = "|";
    add_child_node(*parent, *ptr);
    *ptr = *parent;

    null_node = new_node(NODE_COMMAND);
    add_child_node(*ptr, null_node);
    *ptr = null_node;
    *first_pipe = 1;

    return *ptr;
}

t_node *p_redirection(t_token *tok, t_cli *cli, t_curr_tok *curr, t_node *ptr, enum e_node_type type) {
    t_node *redirection_node = new_node(type);
    set_node_val_str(redirection_node, tok->text);

    if (!redirection_node) {
        free_node_tree(ptr);
        free_token(tok);
        return NULL;
    }

    free_token(tok);
    tok = get_token(cli, curr);
    if (tok == EOF_TOKEN) {
        free_node_tree(ptr);
        return NULL;
    }

    t_node *file_node = new_node(NODE_FILE);
    set_node_val_str(file_node, tok->text);
    if (!file_node) {
        free_node_tree(ptr);
        free_token(tok);
        return NULL;
    }

    add_child_node(redirection_node, file_node);
    add_child_node(ptr, redirection_node);

    return ptr;
}

t_node *p_heredoc(t_token *tok, t_cli *cli, t_curr_tok *curr, t_node *ptr)
{
    t_node *redirection_node = new_node(NODE_HEREDOC);
    set_node_val_str(redirection_node, tok->text);

    if (!redirection_node) {
        free_node_tree(ptr);
        free_token(tok);
        return NULL;
    }

    free_token(tok);
    tok = get_token(cli, curr);
    if (tok == EOF_TOKEN) {
        free_node_tree(ptr);
        return NULL;
    }

    char tmp_filename[] = "/tmp/heredocXXXXXX";
    int tmp_fd = mkstemp(tmp_filename);
    if (tmp_fd == -1) {
        free_node_tree(ptr);
        free_token(tok);
        return NULL;
    }

    char *line = NULL;

        pid_t pid;
        int pipe_fd[2];

        if (pipe(pipe_fd) < 0) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) {
            close(pipe_fd[1]); // Close the write end of the pipe in the child

            char buffer[4096];
            ssize_t bytes_read;
            
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);

            // Read from the pipe and write to the temp file
            while ((bytes_read = read(pipe_fd[0], buffer, sizeof(buffer) - 1)) > 0) {
                buffer[bytes_read] = '\0';
                write(tmp_fd, buffer, bytes_read);
            }

            exit(EXIT_SUCCESS);
        } 
        else {
            close(pipe_fd[0]); // Close the read end of the pipe in the parent

			struct s_word *w = NULL;
			char * content;
			int expanding = 1;
			
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
            while (content && (ft_strncmp(content, tok->text, ft_strlen(content) - 1) != 0 ))
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
				// printf("strlentok %zu\n", ft_strlen(content));
            }
            close(pipe_fd[1]); // Close the write end of the pipe after done writing
            wait(NULL);
        }
        free_token(tok);
        t_node *file_node = new_node(NODE_FILE);
        set_node_val_str(file_node, tmp_filename);
        if (!file_node) {
            free_node_tree(ptr);
            return NULL;
        }
        add_child_node(redirection_node, file_node);
        add_child_node(ptr, redirection_node);


    return ptr;
}

t_node *p_word(t_token *tok, t_node *ptr, enum e_node_type type) {
    t_node *word = new_node(type);
    set_node_val_str(word, tok->text);

    if (!word) {
        free_node_tree(ptr);
        free_token(tok);
        return NULL;
    }
    add_child_node(ptr, word);

    return ptr;
}

t_node *parse_cmd(t_token *tok, t_curr_tok *curr) {
    t_node *ptr;
    t_node *parent;
    t_cli *cli;
    enum e_node_type type;
    int first_pipe = 0;

    if (!tok || !curr)
        return NULL;

    type = get_node_type(curr->tok_type);    
    ptr = new_node(type);
    parent = ptr;
    if (!ptr)
        return free_token(tok), NULL;

    cli = tok->cli;
    do {
        if (tok->text[0] == '\n')
        {
            free_token(tok);
            break;
        }
        type = get_node_type(curr->tok_type);   

        if (type == NODE_PIPE) {
            ptr = p_pipe(&ptr, &parent, &first_pipe);
        } else if (type == NODE_INPUT || type == NODE_OUTPUT || type == NODE_APPEND) {
            ptr = p_redirection(tok, cli, curr, ptr, type);
        } else if (type == NODE_HEREDOC) {
            ptr = p_heredoc(tok, cli, curr, ptr);
        } else {
            ptr = p_word(tok, ptr, type);
        }
    } while ((tok = get_token(cli, curr)) != EOF_TOKEN);
    return parent;
}

