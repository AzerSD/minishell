/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:37:53 by asioud            #+#    #+#             */
/*   Updated: 2023/07/02 16:07:14 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*handle_dollar_sign(t_cli *cli, t_curr_tok *curr)
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
			cli->cur_pos = cli->buff_size;
			fprintf(stderr, "error: missing closing brace '%c'\n", nc);
			return (EOF_TOKEN);
		}
		while (cb_index--)
			add_to_buf(get_next_char(cli), curr);
	}
	else if (isalnum(nc) || nc == '*' || nc == '@' || nc == '#' || nc == '!'
		|| nc == '?' || nc == '$')
		add_to_buf(get_next_char(cli), curr);
	return (NULL);
}

void	handle_pipe(t_cli *cli, t_curr_tok *curr, int *endloop)
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

int	handle_output_redirection(t_cli *cli, t_curr_tok *curr, int *endloop,
		char nc)
{
	if (nc == '>')
	{
		curr->tok_type = TOKEN_OUTPUT;
		add_to_buf('>', curr);
		nc = peek_char(cli);
		if (nc == '>')
		{
			curr->tok_type = TOKEN_APPEND;
			add_to_buf('>', curr);
			nc = get_next_char(cli);
		}
	}
	else
	{
		add_to_buf(nc, curr);
	}
	*endloop = 1;
	return (1);
}

int	handle_input_redirection(t_cli *cli, t_curr_tok *curr, int *endloop,
		char nc)
{
	if (nc == '<')
	{
		curr->tok_type = TOKEN_INPUT;
		add_to_buf('<', curr);
		nc = peek_char(cli);
		if (nc == '<')
		{
			curr->tok_type = TOKEN_HEREDOC;
			add_to_buf('<', curr);
			nc = get_next_char(cli);
		}
	}
	else
	{
		add_to_buf(nc, curr);
	}
	*endloop = 1;
	return (1);
}

void	handle_redirection(t_cli *cli, t_curr_tok *curr, int *endloop, char nc)
{
	if (curr->tok_buff_index > 0)
	{
		*endloop = 1;
		unget_char(cli);
		return ;
	}
	if (nc == '>')
		handle_output_redirection(cli, curr, endloop, nc);
	else if (nc == '<')
		handle_input_redirection(cli, curr, endloop, nc);
}
