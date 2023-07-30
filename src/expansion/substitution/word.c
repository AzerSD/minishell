/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 15:09:50 by asioud            #+#    #+#             */
/*   Updated: 2023/07/03 20:23:02 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_word(struct s_word *word, int *in_double_quotes)
{
	char	*p;

	p = word->data;
	while (*p)
	{
		handle_char(&p, in_double_quotes);
	}
	word->len = ft_strlen(word->data);
}

void	substitute_norm(char **tmp, char **tmp2, char *(func)(char *), \
	size_t *len, char **p)
{
	*tmp = my_malloc(&g_shell.memory, *len + 1);
	if (!*tmp)
	{
		(*p) += *len;
		return ;
	}
	ft_strncpy(*tmp, *p, *len);
	(*tmp)[(*len)--] = '\0';
	if (func)
	{
		*tmp2 = func(*tmp);
		if (*tmp2 == INVALID_VAR)
			*tmp2 = NULL;
		if (*tmp2)
			free(*tmp);
	}
	else
		*tmp2 = *tmp;
}

int	substitute_word(char **pstart, char **p, size_t len, \
	char *(func)(char *), int add_quotes)
{
	char	*tmp;
	char	*tmp2;
	size_t	i;

	substitute_norm(&tmp, &tmp2, func, &len, p);
	if (!tmp2)
		return (0);
	i = (*p) - (*pstart);
	tmp = quote_val(tmp2, add_quotes);
	free(tmp2);
	if (tmp)
	{
		tmp2 = substitute_str(*pstart, tmp, i, i + len);
		if (tmp2)
		{
			(*pstart) = tmp2;
			len = ft_strlen(tmp);
		}
	}
	(*p) = (*pstart) + i + len - 1;
	return (1);
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

	word = my_malloc(&g_shell.memory, sizeof(struct s_word));
	if (!word)
		return (NULL);
	len = ft_strlen(str);
	data = my_malloc(&g_shell.memory, len + 1);
	if (!data)
	{
		free(word);
		return (NULL);
	}
	ft_strcpy(data, str);
	word->data = data;
	word->len = len;
	word->next = NULL;
	return (word);
}
