/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 22:49:41 by asioud            #+#    #+#             */
/*   Updated: 2023/07/02 00:42:38 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_single_quotes(char **p, int *in_double_quotes, \
		int *in_single_quotes)
{
	if (**p == '\'' && !*in_double_quotes)
	{
		*in_single_quotes = !(*in_single_quotes);
		(*p)++;
	}
}

void	check_double_quotes(char **p, int *in_double_quotes, \
	int in_single_quotes)
{
	if (**p == '"' && !in_single_quotes)
	{
		*in_double_quotes = !(*in_double_quotes);
		(*p)++;
	}
}

void	check_backslash(char **p, int *escaped)
{
	if (**p == '\\')
	{
		*escaped = 1;
	}
}

void	check_backtick(char **pstart, char **p)
{
	size_t	len;

	if (**p == '`')
	{
		len = find_closing_quote(*p);
		if (len != 0)
		{
			substitute_word(pstart, p, len + 1, command_substitute, 0);
		}
	}
}

void	check_dollar_sign(char **pstart, char **p, int in_single_quotes,
	int *escaped)
{
	char	c;
	char	*p2;

	if (**p == '$' && !in_single_quotes && !(*escaped))
	{
		c = (*p)[1];
		if (c == '\"')
			(*pstart)++;
		else if (c == '?')
			substitute_word(pstart, p, 2, var_expand, 0);
		else
		{
			if (!ft_isalpha((*p)[1]) && (*p)[1] != '_')
				return ;
			p2 = *p + 1;
			while (ft_isalnum(*p2) || *p2 == '_')
				p2++;
			if (p2 == *p + 1)
				return ;
			substitute_word(pstart, p, p2 - *p, var_expand, 0);
		}
	}
	else if (*escaped)
		(*p)++;
}
