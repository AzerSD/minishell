/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 01:58:16 by asioud            #+#    #+#             */
/*   Updated: 2023/06/09 02:10:11 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <unistd.h>
#include <stdio.h>

#include "../core/shell.h"
#include "parser.h"
#include "tokenizer.h"
#include "node.h"
#include "lexer.h"

enum e_node_type get_node_type(parse_state state)
{
	if (state == PARSE_DEFAULT)
		return NODE_COMMAND;
	else if (state == PARSE_ASSIGNMENT)
		return NODE_ASSIGNMENT;
	else if (state == PARSE_PIPE)
		return NODE_PIPE;
	else
		return NODE_VAR;
}

t_node *parse_cmd(t_token *tok, t_curr_tok	*curr)
{
	t_node				*cmd;
	t_cli				*cli;
	t_node				*word;
	t_node				*parent = NULL;
	enum e_node_type	type;

	if (!tok || !curr)
		return NULL;

	type = get_node_type(curr->parse_state);
	cmd = new_node(type);
	if (!cmd)
		return (free_token(tok), NULL);

	parent = cmd;
	cli = tok->cli;


	do
	{
		if (tok->text[0] == '\n')
		{
			free_token(tok);
			break;
		}
		type = get_node_type(curr->parse_state);
		word = new_node(type);
		if (!word)
		{
			free_node_tree(cmd);
			free_token(tok);
			return NULL;
		}
		set_node_val_str(word, tok->text);
		if (type != NODE_PIPE)
			add_child_node(parent, word);
		else
		{
			// parent = word;
			// add_child_node(parent, cmd);
			// cmd = parent;
		}
		free_token(tok);
	} while ((tok = get_token(cli, curr)) != EOF_TOKEN);

	return cmd;
}
