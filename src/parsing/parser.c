/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 01:58:16 by asioud            #+#    #+#             */
/*   Updated: 2023/06/08 11:07:09 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <unistd.h>
#include <stdio.h>

#include "../core/shell.h"
#include "parser.h"
#include "tokenizer.h"
#include "node.h"
#include "lexer.h"


t_node *parse_cmd(t_token *tok, t_curr_tok	*curr)
{
	t_node		*cmd;
	t_cli		*cli;
	t_node		*word;

	if (!tok || !curr)
		return NULL;

	if (curr->parse_state == PARSE_DEFAULT)
		cmd = new_node(NODE_COMMAND);
	else if (curr->parse_state == PARSE_ASSIGNMENT)
		cmd = new_node(NODE_ASSIGNMENT);
	else
		cmd = NULL;
	if (!cmd)
	{
		free_token(tok);
		return NULL;
	}
	cli = tok->cli;
	do
	{
		if (tok->text[0] == '\n')
		{
			free_token(tok);
			break;
		}
		word = new_node(NODE_VAR);
		if (!word)
		{
			free_node_tree(cmd);
			free_token(tok);
			return NULL;
		}
		set_node_val_str(word, tok->text);
		add_child_node(cmd, word);
		free_token(tok);
	} while ((tok = get_token(cli, curr)) != EOF_TOKEN);
	return cmd;
}
