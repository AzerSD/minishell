/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:05:17 by asioud            #+#    #+#             */
/*   Updated: 2023/06/23 18:09:15 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_word	*make_word_if(struct s_word *words, char *pstart)
{
	words = make_word(pstart);
	if (!words)
	{
		fprintf(stderr, "error: insufficient memory\n");
		free(pstart);
		return (NULL);
	}
	return (words);
}

void	check_double_quotes(char **p, int *in_double_quotes)
{
	if (**p == '"')
	{
		*in_double_quotes = !(*in_double_quotes);
		(*p)++;
	}
}

void	check_backslash(char **p)
{
	if (**p == '\\')
	{
		(*p)++;
	}
}

void	check_single_quotes(char **p, int in_double_quotes)
{
	if (**p == '\'' && !in_double_quotes)
	{
		*p += find_closing_quote(*p);
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

void	check_dollar_sign(char **pstart, char **p)
{
	char c, *p2;
	if (**p == '$')
	{
		c = (*p)[1];
		if (c == '?')
		{
			substitute_word(pstart, p, 2, var_expand, 0);
		}
		else
		{
			if (!isalpha((*p)[1]) && (*p)[1] != '_')
			{
				return ;
			}
			p2 = *p + 1;
			while (*p2)
			{
				if (!isalnum(*p2) && *p2 != '_')
					break ;
				p2++;
			}
			if (p2 == *p + 1)
			{
				return ;
			}
			substitute_word(pstart, p, p2 - *p, var_expand, 0);
		}
	}
}

struct s_word	*expand(char *orig_word)
{
	char			*pstart;
	char			*p;
	size_t			i;
	int				in_double_quotes;
	struct s_word	*words;

	in_double_quotes = 0;
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
		check_double_quotes(&p, &in_double_quotes);
		check_backslash(&p);
		check_single_quotes(&p, in_double_quotes);
		check_backtick(&pstart, &p);
		check_dollar_sign(&pstart, &p);
		p++;
	}
	words = make_word_if(words, pstart);
	if (!words)
	{
		return (NULL);
	}
	free(pstart);
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
