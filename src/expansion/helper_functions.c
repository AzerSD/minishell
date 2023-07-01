/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:01:00 by asioud            #+#    #+#             */
/*   Updated: 2023/03/30 19:01:00 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*wordlist_to_str(struct s_word *word)
{
	size_t len;
	struct s_word *w;
	char *str;
	char *str2;

	if (!word)
		return (NULL);
	len = 0;
	w = word;
	while (w)
	{
		len += w->len + 1;
		w = w->next;
	}
	str = my_malloc(&shell.memory, len + 1);
	if (!str)
	{
		return (NULL);
	}
	str2 = str;
	w = word;
	while (w)
	{
		sprintf(str2, "%s ", w->data);
		str2 += w->len + 1;
		w = w->next;
	}
	str2[-1] = '\0';
	return (str);
}

void	delete_char_at(char *str, size_t index)
{
	char	*p1;
	char	*p2;

	p1 = str + index;
	p2 = p1 + 1;
	while (*p1)
		*p1++ = *p2++;
}

int	is_name(char *str)
{
	if (!isalpha(*str) && *str != '_')
		return (0);
	while (*++str)
		if (!isalnum(*str) && *str != '_')
			return (0);
	return (1);
}

char	*substitute_str(char *s1, char *s2, size_t start, size_t end)
{
	char before[start + 1];
	size_t afterlen;
	afterlen = strlen(s1) - end + 1;
	char after[afterlen];
	size_t totallen;
	char *final;

	strncpy(before, s1, start);
	before[start] = '\0';
	strcpy(after, s1 + end + 1);
	totallen = start + afterlen + strlen(s2);
	final = my_malloc(&shell.memory, totallen + 1);
	if (!final)
	{
		fprintf(stderr,
			"error: insufficient memory to perform variable substitution\n");
		return (NULL);
	}
	if (!totallen)
		final[0] = '\0';
	else
	{
		strcpy(final, before);
		strcat(final, s2);
		strcat(final, after);
	}
	return (final);
}
