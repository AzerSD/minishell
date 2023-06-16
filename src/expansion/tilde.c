/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:15:34 by asioud            #+#    #+#             */
/*   Updated: 2023/03/30 17:15:34 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief perform tilde expansion.
 * @returns the malloc'd expansion of the tilde prefix, NULL if expansion failed.
*/
char	*tilde_expansion(char *s)
{
	char					*home;
	size_t					len;
	char					*s2;
	struct s_symtab_entry	*entry;
	struct passwd			*pass;

	home = NULL;
	len = strlen(s);
	s2 = NULL;
	/* null tilde prefix. substitute with the value of home */
	if (len == 1)
	{
		entry = get_symtab_entry("HOME");
		if (entry && entry->val)
			home = entry->val;
		else
		{
			/*
				* POSIX doesn't say what to do if $HOME is null/unset.. we follow
				* what bash does,
				which is searching our home directory in the password
				* database.
				*/
			pass = getpwuid(getuid());
			if (pass)
			{
				/* get the value of home */
				home = pass->pw_dir;
			}
		}
	}
	else
	{
		/* we have a login name */
		pass = getpwnam(s + 1);
		if (pass)
			home = pass->pw_dir;
	}
	/* we have a NULL value */
	if (!home)
		return NULL;
	/* return the home dir we've found */
	s2 = malloc(strlen(home) + 1);
	if (!s2)
		return NULL;
	strcpy(s2, home);
	return s2;
}
