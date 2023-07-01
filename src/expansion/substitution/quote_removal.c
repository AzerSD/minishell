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

void	handle_char(char **p, int *in_double_quotes)
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
	else if (**p == '\v' || **p == '\f' || **p == '\t' || **p == '\r'
			|| **p == '\n')
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

void process_word(struct s_word *word, int *in_double_quotes) {
	char	*p;

	p = word->data;
	while (*p)
	{
		handle_char(&p, in_double_quotes);
	}
	word->len = strlen(word->data);
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

size_t	find_closing_brace(char *data)
{
	char		opening_brace;
	char		closing_brace;
	size_t		ob_count;
	size_t		cb_count;
	size_t		i;
	size_t		len;
	char		quote;

	opening_brace = data[0];
	if (opening_brace != '{' && opening_brace != '(')
		return (0);
	if (opening_brace == '{')
		closing_brace = '}';
	else
		closing_brace = ')';
	ob_count = 1;
	cb_count = 0;
	i = 0;
	len = strlen(data);
	while (++i < len)
	{
		if ((data[i] == '"') || (data[i] == '\'') || (data[i] == '`'))
		{
			if (data[i - 1] == '\\')
				continue ;
			quote = data[i];
			while (++i < len)
			{
				if (data[i] == quote && data[i - 1] != '\\')
					break ;
			}
			if (i == len)
				return (0);
			continue ;
		}
		if (data[i - 1] != '\\')
		{
			if (data[i] == opening_brace)
				ob_count++;
			else if (data[i] == closing_brace)
				cb_count++;
		}
		if (ob_count == cb_count)
			break ;
	}
	if (ob_count != cb_count)
		return (0);
	return (i);
}
