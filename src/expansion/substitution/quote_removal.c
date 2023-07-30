/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:19:36 by asioud            #+#    #+#             */
/*   Updated: 2023/03/30 17:19:36 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quote_chars(char **p, int *in_double_quotes)
{
	if (**p == '"')
	{
		*in_double_quotes = !*in_double_quotes;
		delete_char_at(*p, 0);
	}
	else if (**p == '\'')
	{
		if (!*in_double_quotes)
		{
			delete_char_at(*p, 0);
			while (**p && **p != '\'')
				(*p)++;
			if (**p == '\'')
				delete_char_at(*p, 0);
		}
		else
			(*p)++;
	}
	else if (**p == '`')
		delete_char_at(*p, 0);
}

void	handle_other_chars(char **p, int *in_double_quotes)
{
	if (**p == '\v' || **p == '\f' || **p == '\t' || **p == '\r' || **p == '\n')
		(*p)++;
	else if (**p == '\\')
	{
		if (*in_double_quotes && ((*p)[1] == '$' || (*p)[1] == '`'
				|| (*p)[1] == '"' || (*p)[1] == '\\' || (*p)[1] == '\n'))
			delete_char_at(*p, 0);
		else if (!*in_double_quotes)
			delete_char_at(*p, 0);
		(*p)++;
	}
	else
		(*p)++;
}

void	handle_char(char **p, int *in_double_quotes)
{
	if (**p == '"' || **p == '\'' || **p == '`')
		handle_quote_chars(p, in_double_quotes);
	else
		handle_other_chars(p, in_double_quotes);
}

void	remove_quotes(struct s_word *wordlist)
{
	int				in_double_quotes;
	struct s_word	*word;

	if (!wordlist)
		return ;
	in_double_quotes = 0;
	word = wordlist;
	while (word)
	{
		process_word(word, &in_double_quotes);
		word = word->next;
	}
}

size_t	find_closing_quote(char *data)
{
	char	quote;
	size_t	i;
	size_t	len;

	quote = data[0];
	if (quote != '\'' && quote != '"' && quote != '`')
		return (0);
	i = 0;
	len = strlen(data);
	while (++i < len)
	{
		if (data[i] == quote)
		{
			if (data[i - 1] == '\\')
				if (quote != '\'')
					continue ;
			return (i);
		}
	}
	return (0);
}
