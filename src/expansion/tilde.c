/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/03/30 17:15:34 by asioud            #+#    #+#             */
/*   Updated: 2023/03/30 17:15:34 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief perform tilde expansion.
 * @returns the malloc'd expansion of the tilde prefix,
	NULL if expansion failed.
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
	if (len == 1)
	{
		entry = get_symtab_entry("HOME");
		if (entry && entry->val)
			home = entry->val;
		else
		{
			pass = getpwuid(getuid());
			if (pass)
			{
				home = pass->pw_dir;
			}
		}
	}
	else
	{
		pass = getpwnam(s + 1);
		if (pass)
			home = pass->pw_dir;
	}
	if (!home)
		return (NULL);
	s2 = my_malloc(&shell.memory, strlen(home) + 1);
	if (!s2)
		return (NULL);
	strcpy(s2, home);
	return (s2);
}
