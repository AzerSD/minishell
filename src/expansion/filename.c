/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathnames.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:33:06 by asioud            #+#    #+#             */
/*   Updated: 2023/03/30 17:33:06 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief perform pathname expansion.
*/
struct s_word	*pathnames_expand(struct s_word *words)
{
	struct s_word	*w;
	struct s_word	*pw;
	char			*p;
	glob_t			glob;
	char			**matches;
	struct s_word	*head;
	struct s_word	*tail;

	w = words;
	pw = NULL;
	while (w)
	{
		p = w->data;
		/* check if we should perform filename globbing */
		if (!has_glob_chars(p, strlen(p)))
		{
			pw = w;
			w = w->next;
			continue ;
		}
		matches = get_filename_matches(p, &glob);
		/* no matches found */
		if (!matches || !matches[0])
			globfree(&glob);
		else
		{
			/* save the matches */
			head = NULL;
			tail = NULL;
			for (size_t j = 0; j < glob.gl_pathc; j++)
			{
				/* skip '..' and '.' */
				if (matches[j][0] == '.' &&
					(matches[j][1] == '.' || matches[j][1] == '\0'
							|| matches[j][1] == '/'))
				{
					continue ;
				}
				/* add the path to the list */
				if (!head)
				{
					/* first item in the list */
					head = make_word(matches[j]);
					tail = head;
				}
				else
				{
					/* add to the list's tail */
					tail->next = make_word(matches[j]);
					if (tail->next)
						tail = tail->next;
				}
			}
			/* add the new list to the existing list */
			if (w == words)
				words = head;
			else if (pw)
				pw->next = head;
			pw = tail;
			tail->next = w->next;
			/* free the word we've just globbed */
			w->next = NULL;
			free_all_words(w);
			w = tail;
			/* free the matches list */
			globfree(&glob);
			/* finished globbing this word */
		}
		pw = w;
		w = w->next;
	}
	return words;
}
