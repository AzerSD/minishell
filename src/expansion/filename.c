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

struct s_glob_info
{
	struct s_word	*words;
	struct s_word	*pw;
	struct s_word	*w;
	struct s_word	*head;
	struct s_word	*tail;
	char			**matches;
	glob_t			glob;
};

void	save_matches(struct s_glob_info *glob_info)
{
	size_t	j;

	j = 0;
	while (j < glob_info->glob.gl_pathc)
	{
		if (glob_info->matches[j][0] != '.' || (glob_info->matches[j][1] != '.'
				&& glob_info->matches[j][1] != '\0'
				&& glob_info->matches[j][1] != '/'))
		{
			if (!glob_info->head)
			{
				glob_info->head = make_word(glob_info->matches[j]);
				glob_info->tail = glob_info->head;
			}
			else
			{
				glob_info->tail->next = make_word(glob_info->matches[j]);
				if (glob_info->tail->next)
				{
					glob_info->tail = glob_info->tail->next;
				}
			}
		}
		j++;
	}
}

void	link_to_existing_list(struct s_glob_info *glob_info)
{
	if (glob_info->w == glob_info->words)
	{
		glob_info->words = glob_info->head;
	}
	else if (glob_info->pw)
	{
		glob_info->pw->next = glob_info->head;
	}
	glob_info->pw = glob_info->tail;
	glob_info->tail->next = glob_info->w->next;
	glob_info->w->next = NULL;
}

struct s_glob_info	init_glob_info(struct s_word *words)
{
	struct s_glob_info	glob_info;

	glob_info.words = words;
	glob_info.pw = NULL;
	glob_info.w = words;
	return (glob_info);
}

struct s_word	*pathnames_expand(struct s_word *words)
{
	struct s_glob_info	glob_info;

	glob_info = init_glob_info(words);
	while (glob_info.w)
	{
		if (has_glob_chars(glob_info.w->data, strlen(glob_info.w->data)))
		{
			glob_info.matches = get_filename_matches(glob_info.w->data, \
				&glob_info.glob);
			if (glob_info.matches && glob_info.matches[0])
			{
				glob_info.head = NULL;
				glob_info.tail = NULL;
				save_matches(&glob_info);
				link_to_existing_list(&glob_info);
				free_all_words(glob_info.w);
				glob_info.w = glob_info.tail;
				globfree(&glob_info.glob);
			}
		}
		glob_info.pw = glob_info.w;
		glob_info.w = glob_info.w->next;
	}
	return (glob_info.words);
}
