/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handlers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 13:07:05 by asioud            #+#    #+#             */
/*   Updated: 2023/07/03 04:45:11 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*handle_quotes(t_cli *cli, t_curr_tok *curr, char nc)
{
	int	closing_quote_index;

	add_to_buf(nc, curr);
	closing_quote_index = find_closing_quote(cli->buffer + cli->cur_pos);
	if (closing_quote_index == 0)
	{
		cli->cur_pos = cli->buff_size;
		ft_printf_fd(STDERR_FILENO, "error: missing closing quote '%c'\n", nc);
		return (EOF_TOKEN);
	}
	while (closing_quote_index--)
		add_to_buf(get_next_char(cli), curr);
	return (NULL);
}

void	handle_backslash(t_cli *cli, t_curr_tok *curr)
{
	char	nc;

	nc = get_next_char(cli);
	if (nc == '\n')
		return ;
	add_to_buf('\\', curr);
	if (nc > 0)
	{
		add_to_buf(nc, curr);
	}
}

void	handle_whitespace(t_curr_tok *curr, int *endloop)
{
	if (curr->tok_buff_index > 0)
		*endloop = 1;
}

void	handle_newline(t_cli *cli, t_curr_tok *curr, int *endloop)
{
	if (curr->tok_buff_index > 0)
		unget_char(cli);
	else
		add_to_buf('\n', curr);
	*endloop = 1;
}

void	handle_equals_sign(t_curr_tok *curr)
{
	curr->tok_type = PARSE_ASSIGNMENT;
	add_to_buf('=', curr);
	return ;
}
