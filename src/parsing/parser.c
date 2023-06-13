/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 01:58:16 by asioud            #+#    #+#             */
/*   Updated: 2023/06/12 22:16:01 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <unistd.h>
#include <stdio.h>

#include "../core/shell.h"
#include "parser.h"
#include "tokenizer.h"
#include "node.h"
#include "lexer.h"
#include "string.h"

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

t_node *parse_redirection(t_node *ptr, t_token *tok, enum e_node_type type)
{
    t_node *redir_node = new_node(type);
    set_node_val_str(redir_node, tok->text);
    if (!redir_node)
    {
        free_node_tree(ptr);
        free_token(tok);
        return NULL;
    }
    add_parent_node(ptr, redir_node);
    ptr = redir_node;
    return ptr;
}

t_node *parse_cmd(t_token *tok, t_curr_tok *curr)
{
    t_node *ptr;
    t_node *parent;
    t_cli *cli;
    t_node *word;
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
        if (type == NODE_PIPE)
        {
            if (first_pipe)
                ptr = parent;

            parent = new_node(NODE_PIPE);
            parent->val.str = "|";
            add_child_node(parent, ptr);
            ptr = parent;

            t_node *null_node = new_node(NODE_COMMAND);
            add_child_node(ptr, null_node);
            ptr = null_node;
            first_pipe = 1;
        }
        else if (type == NODE_INPUT || type == NODE_OUTPUT || type == NODE_APPEND || type == NODE_HEREDOC)
        {
            if (first_pipe)
                ptr = parent;
            printf("hiiiiiiii\n");
            parent = new_node(type);
            parent->val.str = curr->tok_buff;
            add_child_node(parent, ptr);
            ptr = parent;

            t_node *null_node = new_node(NODE_COMMAND);
            add_child_node(ptr, null_node);
            ptr = null_node; 
        }
        else
        {
            word = new_node(type);
            set_node_val_str(word, tok->text);
            if (!word)
            {
                free_node_tree(ptr);
                free_token(tok);
                return NULL;
            }
            add_child_node(ptr, word);
        }
        free_token(tok);
    } while ((tok = get_token(cli, curr)) != EOF_TOKEN);
    return parent;
}

