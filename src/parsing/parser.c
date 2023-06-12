/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 01:58:16 by asioud            #+#    #+#             */
/*   Updated: 2023/06/12 02:08:17 by asioud           ###   ########.fr       */
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
	else
		return NODE_VAR;
}

t_node *parse_cmd(t_token *tok, t_curr_tok *curr)
{
    t_node *ptr;
    t_node *parent;
    t_cli *cli;
    t_node *word;
    t_node *null_node;
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

            null_node = new_node(NODE_COMMAND);
            add_child_node(ptr, null_node);
            ptr = null_node;
            first_pipe = 1;
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
