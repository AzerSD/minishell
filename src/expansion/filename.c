/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:33:06 by asioud            #+#    #+#             */
/*   Updated: 2023/03/30 17:33:06 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_matches(struct s_word **head, struct s_word **tail, glob_t *glob,
			char **matches);
void	link_to_existing_list(struct s_word **words, struct s_word **pw,
			struct s_word **head, struct s_word **tail, struct s_word **w);

struct s_word	*pathnames_expand(struct s_word *words)
{
	struct s_word *w;
	struct s_word *pw;
	char *p;
	glob_t glob;
	char **matches;
	struct s_word *head;
	struct s_word *tail;

	w = words;
	pw = NULL;
	while (w)
	{
		p = w->data;
		if (!has_glob_chars(p, strlen(p)))
		{
			pw = w;
			w = w->next;
			continue ;
		}
		matches = get_filename_matches(p, &glob);
		if (!matches || !matches[0])
		{
			globfree(&glob);
		}
		else
		{
			head = NULL;
			tail = NULL;
			save_matches(&head, &tail, &glob, matches);
			link_to_existing_list(&words, &pw, &head, &tail, &w);
			free_all_words(w);
			w = tail;
			globfree(&glob);
		}
		pw = w;
		w = w->next;
	}
	return (words);
}

void	save_matches(struct s_word **head, struct s_word **tail, glob_t *glob,
		char **matches)
{
	for (size_t j = 0; j < glob->gl_pathc; j++)
	{
		if (matches[j][0] == '.' &&
			(matches[j][1] == '.' || matches[j][1] == '\0'
					|| matches[j][1] == '/'))
		{
			continue ;
		}
		if (!*head)
		{
			*head = make_word(matches[j]);
			*tail = *head;
		}
		else
		{
			(*tail)->next = make_word(matches[j]);
			if ((*tail)->next)
				*tail = (*tail)->next;
		}
	}
}

void	link_to_existing_list(struct s_word **words, struct s_word **pw,
		struct s_word **head, struct s_word **tail, struct s_word **w)
{
	if (*w == *words)
		*words = *head;
	else if (*pw)
		(*pw)->next = *head;
	*pw = *tail;
	(*tail)->next = (*w)->next;
	(*w)->next = NULL;
}
