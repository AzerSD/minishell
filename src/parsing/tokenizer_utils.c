/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 13:03:57 by asioud            #+#    #+#             */
/*   Updated: 2023/07/03 20:15:46 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_variable_name(const char *str)
{
	if (!str || !*str)
		return (0);
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (*++str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
	}
	return (1);
}

void	add_to_buf(char c, t_curr_tok *curr)
{
	char	*tmp;

	curr->tok_buff[curr->tok_buff_index++] = c;
	if (curr->tok_buff_index >= curr->tok_buff_size)
	{
		tmp = ft_realloc(curr->tok_buff, curr->tok_buff_size * 2);
		if (!tmp)
		{
			errno = ENOMEM;
			return ;
		}
		curr->tok_buff = tmp;
		curr->tok_buff_size *= 2;
	}
}

void	free_token(t_token *tok)
{
	if (tok->text)
		free(tok->text);
	free(tok);
}

enum e_node_type	get_node_type(t_token_type state)
{
	if (state == PARSE_DEFAULT)
		return (NODE_COMMAND);
	else if (state == PARSE_ASSIGNMENT)
		return (NODE_ASSIGNMENT);
	else if (state == TOKEN_PIPE)
		return (NODE_PIPE);
	else if (state == TOKEN_OUTPUT)
		return (NODE_OUTPUT);
	else if (state == TOKEN_INPUT)
		return (NODE_INPUT);
	else if (state == TOKEN_APPEND)
		return (NODE_APPEND);
	else if (state == TOKEN_HEREDOC)
		return (NODE_HEREDOC);
	else
		return (NODE_VAR);
}
