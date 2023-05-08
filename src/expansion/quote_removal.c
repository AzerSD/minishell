/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qutation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:19:36 by asioud            #+#    #+#             */
/*   Updated: 2023/03/30 17:19:36 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

/**
 * @brief perform quote removal.
*/
void	remove_quotes(struct s_word *wordlist)
{
	int				in_double_quotes;
	struct s_word	*word;
	char			*p;

	if (!wordlist)
		return ;
	in_double_quotes = 0;
	word = wordlist;
	while (word)
	{
		p = word->data;
		while (*p)
		{
			switch (*p)
			{
			case '"':
				/* toggle quote mode */
				in_double_quotes = !in_double_quotes;
				delete_char_at(p, 0);
				break ;
			case '\'':
				/* don't delete if inside double quotes */
				if (in_double_quotes)
				{
					p++;
					break ;
				}
				delete_char_at(p, 0);
				/* find the closing quote */
				while (*p && *p != '\'')
				{
					p++;
				}
				/* and remove it */
				if (*p == '\'')
				{
					delete_char_at(p, 0);
				}
				break ;
			case '`':
				delete_char_at(p, 0);
				break ;
			case '\v':
			case '\f':
			case '\t':
			case '\r':
			case '\n':
				p++;
				break ;
			case '\\':
				if (in_double_quotes)
				{
					switch (p[1])
					{
					/*
						* in double quotes,
							backslash preserves its special quoting
						* meaning only when followed by one of the following chars.
						*/
					case '$':
					case '`':
					case '"':
					case '\\':
					case '\n':
						delete_char_at(p, 0);
						p++;
						break ;
					default:
						p++;
						break ;
					}
				}
				else
				{
					/* parse single-character backslash quoting. */
					delete_char_at(p, 0);
					p++;
				}
				break ;
			default:
				p++;
				break ;
			}
		}
		/* update the word's length */
		word->len = strlen(word->data);
		/* move on to the next word */
		word = word->next;
	}
}

/**
 * @brief find the closing quote that matches the opening quote, 
 * @param data the string(starting from the opening quote) to search in.
 * @returns 0 if no matching closing quote was found, 
 * 			otherwise the index of the quote
*/
size_t	find_closing_quote(char *data)
{
	char	quote;
	size_t	i;
	size_t	len;

	quote = data[0];
	if (quote != '\'' && quote != '"' && quote != '`')
		return (0);
	i = 0, len = strlen(data);
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

/**
 * @brief find the closing brace that matches the opening brace, which is the first
 * char of the data string.
 * @returns the zero-based index of the closing brace.. a return value of 0
 * means we didn't find the closing brace.
*/
size_t	find_closing_brace(char *data)
{
	char	opening_brace;
	char	closing_brace;
	size_t	ob_count;
	size_t	cb_count;
	size_t	i;
	size_t	len;
	char	quote;

	/* check the type of opening brace we have */
	opening_brace = data[0];
	if (opening_brace != '{' && opening_brace != '(')
		return (0);
	/* determine the closing brace according to the opening brace */
	if (opening_brace == '{')
		closing_brace = '}';
	else
		closing_brace = ')';
	/* find the matching closing brace */
	ob_count = 1, cb_count = 0;
	i = 0, len = strlen(data);
	while (++i < len)
	{
		if ((data[i] == '"') || (data[i] == '\'') || (data[i] == '`'))
		{
			/* skip escaped quotes */
			if (data[i - 1] == '\\')
				continue ;
			/* skip quoted substrings */
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
		/* keep the count of opening and closing braces */
		if (data[i - 1] != '\\')
		{
			if (data[i] == opening_brace)
				ob_count++;
			else if (data[i] == closing_brace)
				cb_count++;
		}
		/* break when we have a matching number of opening and closing braces */
		if (ob_count == cb_count)
			break ;
	}
	if (ob_count != cb_count)
		return (0);
	return (i);
}
