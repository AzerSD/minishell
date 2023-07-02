/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 01:58:27 by asioud            #+#    #+#             */
/*   Updated: 2023/07/02 20:09:58 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * This tokenizer will use the helper functions created by the lexer.c
 * to scan the input and turn them into tokens
*/

#include "minishell.h"

static void		*init_curr_tok_buff(t_cli *cli, t_curr_tok *curr);

static t_token	*create_token(char *str)
{
	t_token	*tok;
	char	*nstr;

	tok = my_malloc(&shell.memory, sizeof(t_token));
	if (!tok)
		return (NULL);
	memset(tok, 0, sizeof(t_token));
	tok->text_len = strlen(str);
	nstr = my_malloc(&shell.memory, tok->text_len + 1);
	if (!nstr)
	{
		free(tok);
		return (NULL);
	}
	strcpy(nstr, str);
	tok->text = nstr;
	return (tok);
}

t_token	*get_token(t_cli *cli, t_curr_tok *curr)
{
	char	nc;
	int		endloop;
	t_token	*tok;

	endloop = 0;
	init_curr_tok(curr);
	nc = get_next_char(cli);
	if (nc == ERRCHAR || nc == EOF || init_curr_tok_buff(cli, curr) != 0)
		return (EOF_TOKEN);
	do
	{
		if (nc == '"' || nc == '\'' || nc == '`')
			handle_quotes(cli, curr, nc);
		else if (nc == '\\')
			handle_backslash(cli, curr);
		else if (nc == '$')
			handle_dollar_sign(cli, curr);
		else if (nc == ' ' || nc == '\t')
			handle_whitespace(curr, &endloop);
		else if (nc == '\n')
			handle_newline(cli, curr, &endloop);
		else if (nc == '=')
			handle_equals_sign(curr);
		else if (nc == '|')
			handle_pipe(cli, curr, &endloop);
		else if (nc == '>' || nc == '<')
			handle_redirection(cli, curr, &endloop, nc);
		else
			add_to_buf(nc, curr);
		if (endloop == 1)
			break ;
	} while ((nc = get_next_char(cli)) != EOF);
	if (curr->tok_buff_index == 0)
		return (EOF_TOKEN);
	if (curr->tok_buff_index >= curr->tok_buff_size)
		curr->tok_buff_index--;
	curr->tok_buff[curr->tok_buff_index] = '\0';
	tok = create_token(curr->tok_buff);
	if (!tok)
	{
		fprintf(stderr, "error: failed to alloc buffer: %s\n", strerror(errno));
		return (EOF_TOKEN);
	}
	tok->cli = cli;
	return (tok);
}

void	init_curr_tok(t_curr_tok *curr)
{
	curr->tok_buff = NULL;
	curr->tok_buff_size = 0;
	curr->tok_buff_index = -1;
	curr->tok_type = PARSE_DEFAULT;
}

static void	*init_curr_tok_buff(t_cli *cli, t_curr_tok *curr)
{
	if (!cli || !cli->buffer || !cli->buff_size)
	{
		errno = ENODATA;
		return (EOF_TOKEN);
	}
	if (!curr->tok_buff)
	{
		curr->tok_buff_size = 1024;
		curr->tok_buff = my_malloc(&shell.memory, curr->tok_buff_size);
		if (!curr->tok_buff)
		{
			errno = ENOMEM;
			return (EOF_TOKEN);
		}
	}
	curr->tok_buff_index = 0;
	curr->tok_buff[0] = '\0';
	return (0);
}
