/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:05:17 by asioud            #+#    #+#             */
/*   Updated: 2023/07/27 23:02:49 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_word	*expand(char *orig_word)
{
	char			*pstart;
	char			*p;
	char			*p2;
	size_t			i;
	size_t			len;
	int				in_double_quotes;
	int				in_var_assign;
	int				var_assign_eq;
	int				expanded;
	int				tilde_quoted;
	int				endme;
	struct s_word	*words;
	char			*tmp;
	char			c;
	char *(*func)(char *);

	if (!orig_word)
		return NULL;
	if (!*orig_word)
		return make_word(orig_word);
	pstart = malloc(strlen(orig_word) + 1);
	if (!pstart)
		return NULL;
	strcpy(pstart, orig_word);
	p = pstart;
	i = 0;
	in_double_quotes = 0;
	in_var_assign = 0;
	var_assign_eq = 0;
	do
	{
		switch (*p)
		{
			case '"':
				in_double_quotes = !in_double_quotes;
				break ;
			case '\\':
				p++;
				break ;
			case '\'':

				if (in_double_quotes)
					break ;
				p += find_closing_quote(p);
				break ;
			case '`':
				if ((len = find_closing_quote(p)) == 0)
					break ;
				substitute_word(&pstart, &p, len + 1, command_substitute, 0);
				break ;

			case '$':
				c = p[1];
				if (c == '?')
				{
					substitute_word(&pstart, &p, 2, var_expand, 0);
					break;
				}
				else
				{
						if (!isalpha(p[1]) && p[1] != '_')
							break ;
						p2 = p + 1;
						while (*p2)
						{
							if (!isalnum(*p2) && *p2 != '_')
								break ;
							p2++;
						}
						if (p2 == p + 1)
							break ;
						substitute_word(&pstart, &p, p2 - p, var_expand, 0);
						break ;
				}
			}

	} while (*(++p));
	words = NULL;
	if (!words)
	{
		words = make_word(pstart);
		if (!words)
		{
			fprintf(stderr, "error: insufficient memory\n");
			free(pstart);
			return NULL;
		}
	}
	free(pstart);
	words = pathnames_expand(words);
	remove_quotes(words);
	return words;
}

char	*word_expand_to_str(char *word)
{
	struct s_word	*w;
	char			*res;

	w = expand(word);
	if (!w)
		return NULL;
	res = wordlist_to_str(w);
	free_all_words(w);
	return res;
}


struct s_word	*make_word(char *str)
{
	struct s_word	*word;
	size_t			len;
	char			*data;

	word = malloc(sizeof(struct s_word));
	if (!word)
		return (NULL);
	len = strlen(str);
	data = malloc(len + 1);
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
