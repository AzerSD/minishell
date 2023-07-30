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
	size_t			len;
	struct s_word	*w;
	char			*str;
	char			*str2;

	if (!word)
		return (NULL);
	len = 0;
	w = word;
	while (w)
	{
		len += w->len + 1;
		w = w->next;
	}
	str = my_malloc(&g_shell.memory, len + 1);
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
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (*++str)
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
	return (1);
}

char	*create_final_string(char *before, char *s2, char *after, char *final)
{
	ft_strcpy(final, before);
	ft_strcat(final, s2);
	ft_strcat(final, after);
	return (final);
}

char	*substitute_str(char *s1, char *s2, size_t start, size_t end)
{
	char	*before;
	size_t	afterlen;
	size_t	totallen;
	char	*after;
	char	*final;

	before = (char *)my_malloc(&g_shell.memory, (start + 1) * sizeof(char));
	ft_strncpy(before, s1, start);
	before[start] = '\0';
	afterlen = ft_strlen(s1) - end + 1;
	after = (char *)my_malloc(g_shell.memory, afterlen * sizeof(char));
	if (!after)
		return (NULL);
	ft_strcpy(after, s1 + end + 1);
	totallen = start + afterlen + ft_strlen(s2);
	final = my_malloc(&g_shell.memory, totallen + 1);
	if (!final)
		return (my_free(&g_shell.memory, final), NULL);
	if (!totallen)
		final[0] = '\0';
	else
		final = create_final_string(before, s2, after, final);
	return (my_free(&g_shell.memory, after), final);
}
