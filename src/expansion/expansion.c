/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:05:17 by asioud            #+#    #+#             */
/*   Updated: 2023/06/27 17:54:00 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	check_single_quotes(char **p, int *in_double_quotes, int *in_single_quotes)
{
	if (**p == '\'' && !*in_double_quotes)
	{
		*in_single_quotes = !(*in_single_quotes);
		(*p)++;
	}
}

void	check_double_quotes(char **p, int *in_double_quotes, int in_single_quotes)
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
		if ((len = find_closing_quote(*p)) != 0)
		{
			substitute_word(pstart, p, len + 1, command_substitute, 0);
		}
	}
}

void	check_tilde(char **pstart, char **p, int in_double_quotes)
{
	char *p2;
	int tilde_quoted;
	int endme;
	int len;

	if (**p == '~' && !in_double_quotes)
	{
		tilde_quoted = 0;
		endme = 0;
		p2 = *p + 1;

		while (*p2)
		{
			if (*p2 == '\\')
			{
				tilde_quoted = 1;
				p2++;
			}
			else if (*p2 == '"' || *p2 == '\'')
			{
				int i = find_closing_quote(p2);
				if (i)
				{
					tilde_quoted = 1;
					p2 += i;
				}
			}
			else if (*p2 == '/')
				endme = 1;

			if (endme)
				break;

			p2++;
		}

		if (tilde_quoted)
		{
			*p = p2;
			return;
		}

		len = p2 - *p;
		substitute_word(pstart, p, len, tilde_expansion, !in_double_quotes);
	}
}

void	check_dollar_sign(char **pstart, char **p, int in_single_quotes, int *escaped)
{
	char c, *p2;

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
			while (*p2)
			{
				if (!ft_isalnum(*p2) && *p2 != '_')
					break ;
				p2++;
			}
			if (p2 == *p + 1)
				return ;

			substitute_word(pstart, p, p2 - *p, var_expand, 0);
		}
	}
	else if (*escaped)
	{
		(*p)++;
	}
}

struct s_word	*expand(char *orig_word)
{
	char			*pstart;
	char			*p;
	size_t			i;
	int				in_double_quotes;
	int				in_single_quotes;
	struct s_word	*words;
	int				escaped;

	in_double_quotes = 0;
	in_single_quotes = 0;
	char			*(*func)(char *);
	if (!orig_word)
		return (NULL);
	if (!*orig_word)
		return (make_word(orig_word));
	pstart = my_malloc(&shell.memory, strlen(orig_word) + 1);
	if (!pstart)
		return (NULL);
	strcpy(pstart, orig_word);
	p = pstart;
	i = 0;
	while (*p)
	{
		escaped = 0;
		check_tilde(&pstart, &p, in_double_quotes);
		check_double_quotes(&p, &in_double_quotes, in_single_quotes);
		check_single_quotes(&p, &in_double_quotes, &in_single_quotes);
		check_backslash(&p, &escaped);
		check_dollar_sign(&pstart, &p, in_single_quotes, &escaped);
		p++;
	}
	words = make_word(pstart);
	if (!words)
	{
		return (NULL);
	}
	
	words = pathnames_expand(words);
	remove_quotes(words);
	return (words);
}


char	*word_expand_to_str(char *word)
{
	struct s_word	*w;
	char			*res;

	w = expand(word);
	if (!w)
		return (NULL);
	res = wordlist_to_str(w);
	free_all_words(w);
	return (res);
}

struct s_word	*make_word(char *str)
{
	struct s_word	*word;
	size_t			len;
	char			*data;

	word = my_malloc(&shell.memory, sizeof(struct s_word));
	if (!word)
		return (NULL);
	len = strlen(str);
	data = my_malloc(&shell.memory, len + 1);
	if (!data)
	{
		free(word);
		return (NULL);
	}
	strcpy(data, str);
	word->data = data;
	word->len = len;
	word->next = NULL;
	return (word);
}

void	free_all_words(struct s_word *first)
{
	struct s_word	*del;

	while (first)
	{
		del = first;
		first = first->next;
		if (del->data)
			free(del->data);
		free(del);
	}
}

