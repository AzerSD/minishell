/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathnames.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/03/30 17:33:06 by asioud            #+#    #+#             */
/*   Updated: 2023/03/30 17:33:06 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	save_matches(struct s_word **head, struct s_word **tail, glob_t *glob,
			char **matches);
void	link_to_existing_list(struct s_word **words, struct s_word **pw,
			struct s_word **head, struct s_word **tail, struct s_word **w);

/**
 * @brief Perform filename globbing on a linked list of words.
 * @param words Pointer to the first word in the linked list.
 * @return The head of the linked list after globbing is completed.
 *
 * Filename globbing is the process of expanding wildcard characters 
 * (`*`, `?`, etc.) in a string to match actual file and directory names.
*/
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

/**
 * @brief Save matches from globbing into a new linked list.
 * @param head Pointer to the head of the new linked list.
 * @param tail Pointer to the tail of the new linked list.
 * @param glob Pointer to a glob_t struct holding the globbing result.
 * @param matches Array of matches from globbing.
 *
 * This function loops over the matched filenames (`matches`),
	skipping entries that are `.` or `..` or start with `./`.
 * It creates a new linked list of words (`head`) from these matches,
	appending new matches to the end (`tail`) of the list.
*/
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

/**
 * @brief Link the new list of matches to the existing list of words.
 * @param words Pointer to the head of the original list of words.


	* @param pw Pointer to the word previous to the one being globbed in the original list.
 * @param head Pointer to the head of the new linked list.
 * @param tail Pointer to the tail of the new linked list.
 * @param w Pointer to the word being globbed in the original list.
 *
 * This function links the new list of matches to the existing list of words. 
 * If the word being expanded is the first word in the list,
	the head of the list is changed.
 * Otherwise,
	the previous word's `next` pointer is updated to point to the new list.
 * Finally, the word that was expanded is freed,
	and `w` is updated to point to the last word that was added (`tail`).
*/
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
