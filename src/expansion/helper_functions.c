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
/**
 * @brief convert a tree of tokens into a command string (i.e. re-create the original
 * command line from the token tree.
 * @returns the malloc'd command string, or NULL if there is an error.
*/
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
	str = malloc(len + 1);
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
	/* remove the last separator */
	str2[-1] = '\0';
	return (str);
}

/*
 * delete the character at the given index in the given str.
 */
void	delete_char_at(char *str, size_t index)
{
	char	*p1;
	char	*p2;

	p1 = str + index;
	p2 = p1 + 1;
	while ((*p1++ = *p2++))
		;
}

/**
 * @brief check if the given str is a valid name.. POSIX says a names can consist of
 * alphanumeric chars and underscores,and start with an alphabetic char or underscore.
 * @returns 1 if str is a valid name, 0 otherwise.
 */
int	is_name(char *str)
{
	if (!isalpha(*str) && *str != '_')
		return (0);
	while (*++str)
		if (!isalnum(*str) && *str != '_')
			return (0);
	return (1);
}

/**
 * @brief substitute the substring of s1, from character start to character end,
 * with the s2 string.
 * start should point to the first char to be deleted from s1.
 * end should point to the last char to be deleted from s, NOT the
 * char coming after it.
 * @returns the malloc'd new string, or NULL on error.
*/
char	*substitute_str(char *s1, char *s2, size_t start, size_t end)
{
	char	before[start + 1];
	size_t	afterlen;
	afterlen = strlen(s1) - end + 1;
	char	after[afterlen];
	size_t	totallen;
	char	*final;

	/* get the prefix (the part before start) */
	strncpy(before, s1, start);
	before[start] = '\0';
	/* get the postfix (the part after end) */
	strcpy(after, s1 + end + 1);
	/* alloc memory for the new string */
	totallen = start + afterlen + strlen(s2);
	final = malloc(totallen + 1);
	if (!final)
	{
		fprintf(stderr,
				"error: insufficient memory to perform variable substitution\n");
		return NULL;
	}
	if (!totallen) /* empty string */
		final[0] = '\0';
	else /* concatenate the three parts into one string */
	{
		strcpy(final, before);
		strcat(final, s2);
		strcat(final, after);
	}
	/* return the new string */
	return final;
}

/**
 * @brief a helper function that calls the other word expansion functions, 
 * which we'll define in the following sections.
 * @param pstart 
 * @param p 
 * @param len 
 * @param func 
 * @param add_quotes 
 * @return int 
 */
int	substitute_word(char **pstart, char **p, size_t len, char *(func)(char *),
		int add_quotes)
{
	char	*tmp;
	char	*tmp2;
	size_t	i;

	tmp = malloc(len + 1);
	if (!tmp)
	{
		(*p) += len;
		return 0;
	}
	strncpy(tmp, *p, len);
	tmp[len--] = '\0';
	
	if (func)
	{
		tmp2 = func(tmp);
		if (tmp2 == INVALID_VAR)
			tmp2 = NULL;
		if (tmp2)
			free(tmp);
	}
	else
		tmp2 = tmp;
	if (!tmp2)
	{
		(*p) += len;
		free(tmp);
		return 0;
	}
	i = (*p) - (*pstart);
	tmp = quote_val(tmp2, add_quotes);
	free(tmp2);
	if (tmp)
	{
		if ((tmp2 = substitute_str(*pstart, tmp, i, i + len)))
		{
			free(*pstart);
			(*pstart) = tmp2;
			len = strlen(tmp);
		}
		free(tmp);
	}

	(*p) = (*pstart) + i + len - 1;
	return 1;
}
