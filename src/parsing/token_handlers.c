/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:37:53 by asioud            #+#    #+#             */
/*   Updated: 2023/06/16 00:09:56 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "../expansion/expansion.h"
#include <stdio.h>


int is_valid_variable_name(const char *str)
{
	if (!str || !*str) return 0;

	if (!isalpha(*str) && *str != '_') return 0;

	while (*++str) {
		if (!isalnum(*str) && *str != '_') return 0;
	}

	return 1;
}

void *handle_quotes(t_cli *cli, t_curr_tok *curr, char nc)
{
	int	closing_quote_index;

	add_to_buf(nc, curr);
	closing_quote_index = find_closing_quote(cli->buffer + cli->cur_pos);
	if (closing_quote_index == 0) /* No matching closing quote found */
	{
		cli->cur_pos = cli->buff_size; /* A.K.A set cursor at EOF */
		fprintf(stderr, "error: missing closing quote '%c'\n", nc);
		return EOF_TOKEN;
	}
	while (closing_quote_index--) /* Add everything after open quote to token_buff */
		add_to_buf(get_next_char(cli), curr);
	return NULL;
}

void handle_backslash(t_cli *cli, t_curr_tok *curr)
{
	char nc;

	nc = get_next_char(cli);
	if (nc == '\n')
		return ;
	add_to_buf('\\', curr);
	if (nc > 0) {
		add_to_buf(nc, curr); /* AKA add characters like \n \0 \r to buff */
	}
}

void *handle_dollar_sign(t_cli *cli, t_curr_tok *curr)
{
	char	nc;
	int		cb_index;

	add_to_buf('$', curr);
	nc = peek_char(cli);
	if (nc == '{' || nc == '(')
	{
		cb_index = find_closing_brace(cli->buffer + cli->cur_pos + 1);
		if (cb_index == 0)
		{
			cli->cur_pos = cli->buff_size; /* A.K.A set cursor at EOF */
			fprintf(stderr, "error: missing closing brace '%c'\n", nc);
			return EOF_TOKEN;
		}
		while (cb_index--)
			add_to_buf(get_next_char(cli), curr);
	}
	else if (isalnum(nc) || nc == '*' || nc == '@' || nc == '#' \
			|| nc == '!' || nc == '?' || nc == '$')
		add_to_buf(get_next_char(cli), curr);
		/** @todo I SHOULD HANDLE `$?` */
	return (NULL);
}

void handle_whitespace(t_curr_tok *curr, int *endloop)
{
	if (curr->tok_buff_index > 0)
		*endloop = 1;
}

void handle_newline(t_cli *cli, t_curr_tok *curr, int *endloop)
{
	if (curr->tok_buff_index > 0)
		unget_char(cli);
	else
		add_to_buf('\n', curr);
	*endloop = 1;
}

void handle_equals_sign(t_curr_tok *curr)
{
	curr->tok_type = PARSE_ASSIGNMENT;	
	add_to_buf('=', curr);
	return ;
}

void handle_pipe(t_cli *cli, t_curr_tok *curr, int *endloop)
{
    if (curr->tok_buff_index > 0)
	{
        *endloop = 1;
		unget_char(cli);
		return ;
	}
	add_to_buf('|', curr);
	curr->tok_type = TOKEN_PIPE;
	*endloop = 1;
}

void handle_redirection(t_cli *cli, t_curr_tok *curr, int *endloop, char nc)
{
    if (curr->tok_buff_index > 0)
    {
        *endloop = 1;
        unget_char(cli);
        return;
    }

    if (nc == '>')
    {
        curr->tok_type = TOKEN_OUTPUT;
        add_to_buf('>', curr);
        nc = get_next_char(cli);
        if (nc == '>')
        {
            curr->tok_type = TOKEN_APPEND;
            add_to_buf('>', curr);
        }
        else
        {
            unget_char(cli);
        }
    }
    else if (nc == '<')
    {
        curr->tok_type = TOKEN_INPUT;
        add_to_buf('<', curr);
        nc = get_next_char(cli);
        if (nc == '<')
        {
            curr->tok_type = TOKEN_HEREDOC;
            add_to_buf('<', curr);
        }
        else
        {
            unget_char(cli);
        }
    }
    else
    {
        add_to_buf(nc, curr);
    }
    *endloop = 1;
}

