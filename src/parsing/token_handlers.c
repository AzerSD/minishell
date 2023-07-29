/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:37:53 by asioud            #+#    #+#             */
/*   Updated: 2023/07/29 22:34:34 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	*handle_dollar_sign(t_cli *cli, t_curr_tok *curr)
{
	char	nc;

	add_to_buf('$', curr);
	nc = peek_char(cli);
	if (ft_isalnum(nc) || nc == '*' || nc == '@' || nc == '#' || nc == '!'
		|| nc == '?' || nc == '$')
		add_to_buf(get_next_char(cli), curr);
	return (NULL);
}

void handle_and(t_cli *cli, t_curr_tok *curr, int *endloop)
{
    char nc = peek_char(cli);
    if (nc == '&')
    {
        add_to_buf('&', curr);
        add_to_buf(get_next_char(cli), curr);
        curr->tok_type = TOKEN_AND;
        *endloop = 1;
    }
    else
    {
        // handle as a single '&' (or error) here
    }
}

void handle_brackets(t_cli *cli, t_curr_tok *curr, int *endloop)
{
    char nc = get_next_char(cli);
    if (nc == '(')
    {
        add_to_buf(nc, curr);
        curr->tok_type = TOKEN_LEFT_BRACKET;
        *endloop = 1;
    }
    else if (nc == ')')
    {
        add_to_buf(nc, curr);
        curr->tok_type = TOKEN_RIGHT_BRACKET;
        *endloop = 1;
    }
    else
    {
        // handle error here
    }
}

void	handle_pipe_or(t_cli *cli, t_curr_tok *curr, int *endloop)
{
   if (curr->tok_buff_index > 0)
    {
        *endloop = 1;
        unget_char(cli);
        return ;
    }
    char nc = peek_char(cli);
    if (nc == '|')
    {
        add_to_buf('|', curr);
        add_to_buf(get_next_char(cli), curr);  // consume the second '|'
        curr->tok_type = TOKEN_OR;
    }
    else
    {
        add_to_buf('|', curr);
        curr->tok_type = TOKEN_PIPE;
    }
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
		add_to_buf(nc, curr);
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
		add_to_buf(nc, curr);
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
