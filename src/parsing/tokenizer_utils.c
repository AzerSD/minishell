/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 13:03:57 by asioud            #+#    #+#             */
/*   Updated: 2023/07/01 13:06:39 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_variable_name(const char *str)
{
	if (!str || !*str)
		return (0);
	if (!isalpha(*str) && *str != '_')
		return (0);
	while (*++str)
	{
		if (!isalnum(*str) && *str != '_')
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
		tmp = realloc(curr->tok_buff, curr->tok_buff_size * 2);
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
