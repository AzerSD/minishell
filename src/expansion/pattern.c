/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:43:01 by asioud            #+#    #+#             */
/*   Updated: 2023/04/03 18:43:01 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	match_prefix(char *pattern, char *str, int longest)
{
	t_match	match;

	init_match(&match);
	if (!pattern || !str)
		return (0);
	if (is_match_found(pattern, longest, &match))
		return (str - match.smatch);
	if (match.lmatch)
		return (match.lmatch - str);
	if (match.smatch)
		return (match.smatch - str);
	return (0);
}

int	match_suffix(char *pattern, char *str, int longest)
{
	char	*s;
	t_match	match;

	init_match(&match);
	match.str = str;
	if (!pattern || !str)
		return (0);
	s = str + ft_strlen(str) - 1;
	check_pattern(pattern, longest, &match, &s);
	if (match.lmatch)
		return (match.lmatch - str);
	if (match.smatch)
		return (match.smatch - str);
	return (0);
}

char	**get_filename_matches(char *pattern, glob_t *matches)
{
	int	res;

	matches->gl_pathc = 0;
	matches->gl_pathv = NULL;
	if (!pattern)
		return (NULL);
	res = glob(pattern, 0, NULL, matches);
	if (res != 0)
	{
		globfree(matches);
		return (NULL);
	}
	return (matches->gl_pathv);
}
