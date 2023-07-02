/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/03/30 17:12:08 by asioud            #+#    #+#             */
/*   Updated: 2023/03/30 17:12:08 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*exit_code_to_str(unsigned char status)
{
	static char str[4];
		// 3 digits and a null terminator should be enough for any exit code
	snprintf(str, sizeof(str), "%d", status);
	return (str);
}

char	*var_expand(char *orig_var_name)
{
	size_t len;
	int get_length;
	char *sub;
	len = strlen(orig_var_name);
	char var_name[len + 1];
	char *empty_val;
	char *tmp;
	char setme;
	struct s_symtab_entry *entry;
	char *p;
	int longest;
	char *p2;
	int expanded;
	char buf[32];

	/* sanity check */
	if (!orig_var_name)
		return (NULL);
	/*
		*  if the var substitution is in the $var format, remove the $.
		*  if it's in the ${var} format, remove the ${}.
		*/
	/* skip the $ */
	orig_var_name++;
	len = strlen(orig_var_name);
	if (*orig_var_name == '{')
	{
		/* remove the } */
		orig_var_name[len - 1] = '\0';
		orig_var_name++;
	}
	/* check we don't have an empty varnamen */
	if (!*orig_var_name)
		return (NULL);
	get_length = 0;
	/* if varnamen starts with #, we need to get the string length */
	if (*orig_var_name == '#')
	{
		/* use of '#' should come with omission of ':' */
		if (strchr(orig_var_name, ':'))
		{
			fprintf(stderr, "error: invalid variable substitution: %s\n",
					orig_var_name);
			return (INVALID_VAR);
		}
		get_length = 1;
		orig_var_name++;
	}
	/* check we don't have an empty varnamen */
	if (!*orig_var_name)
		return (NULL);
	if (strcmp(orig_var_name, "?") == 0)
	{
		char *exit_code_str = exit_code_to_str(shell.status);
		char *exit_code_copy = strdup(exit_code_str);
		if (exit_code_copy == NULL)
		{
			fprintf(stderr,
					"error: failed to allocate memory for exit code\n");
			return (INVALID_VAR);
		}
		return (exit_code_copy);
	}
	/*
		* search for a colon,
			which we use to separate the variable name from the
		* value or substitution we are going to perform on the variable.
		*/
	sub = strchr(orig_var_name, ':');
	if (!sub) /* we have a substitution without a colon */
	{
		/* search for the char that indicates what type of substitution we need to do */
		sub = strchr_any(orig_var_name, "-=?+%#");
	}
	/* get the length of the variable name (without the substitution part) */
	len = sub ? (size_t)(sub - orig_var_name) : strlen(orig_var_name);
	/* if we have a colon+substitution, skip the colon */
	if (sub && *sub == ':')
	{
		sub++;
	}
	/* copy the varnamen to a buffer */
	strncpy(var_name, orig_var_name, len);
	var_name[len] = '\0';

	/*
		* commence variable substitution.
		*/
	empty_val = "";
	tmp = NULL;
	setme = 0;
	entry = get_symtab_entry(var_name);
	tmp = (entry && entry->val && entry->val[0]) ? entry->val : empty_val;
	/*
		* first case: variable is unset or empty.
		*/
	if (!tmp || tmp == empty_val)
	{
		/* do we have a substitution clause? */
		if (sub && *sub)
		{
			/* check the substitution operation we need to perform */
			switch (sub[0])
			{
			case '-': /* use default value */
				tmp = sub + 1;
				break ;
			case '=': /* assign the variable a value */
				/*
					* NOTE: only variables,
						not positional or special parameters can be
					*       assigned this way (we'll fix this later).
					*/
				tmp = sub + 1;
				/*
					* assign the EXPANSION OF tmp, not tmp
					* itself, to var_name (we'll set the value below).
					*/
				setme = 1;
				break ;
			case '?': /* print error msg if variable is null/unset */
				if (sub[1] == '\0')
					fprintf(stderr, "error: %s: parameter not set\n",
							var_name);
				else
					fprintf(stderr, "error: %s: %s\n", var_name, sub + 1);
				return (INVALID_VAR);
			/* use alternative value (we don't have alt. value here) */
			case '+':
				return (NULL);
			/*
				* pattern matching notation. can't match anything
				* if the variable is not defined, now can we?
				*/
			case '#':
			case '%':
				break ;
			default: /* unknown operator */
				return (INVALID_VAR);
			}
		}
		/* no substitution clause. return NULL as the variable is unset/null */
		else
			tmp = empty_val;
	}
	/*
	* second case: variable is set/not empty.
	*/
	else
	{
		/* do we have a substitution clause? */
		if (sub && *sub)
		{
			/* check the substitution operation we need to perform */
			switch (sub[0])
			{
			case '-': /* use default value */
			case '=': /* assign the variable a value */
			case '?': /* print error msg if variable is null/unset */
				break ;
			/* use alternative value */
			case '+':
				tmp = sub + 1;
				break ;
			/*
				* for the prefix and suffix matching routines (below).
				* bash expands the pattern part, but ksh doesn't seem to do
				* the same (as far as the manpage is concerned). we follow ksh.
				*/
			case '%': /* match suffix */
				sub++;
				/* perform word expansion on the value */
				p = word_expand_to_str(tmp);
				/* word expansion failed */
				if (!p)
					return (INVALID_VAR);
				longest = 0;
				/* match the longest or shortest suffix */
				if (*sub == '%')
					longest = 1, sub++;
				/* perform the match */
				if ((len = match_suffix(sub, p, longest)) == 0)
					return (p);
				/* return the match */
				p2 = my_malloc(&shell.memory, len + 1);
				if (p2)
				{
					strncpy(p2, p, len);
					p2[len] = '\0';
				}
				free(p);
				return (p2);
			case '#': /* match prefix */
				sub++;
				/* perform word expansion on the value */
				p = word_expand_to_str(tmp);
				/* word expansion failed */
				if (!p)
					return (INVALID_VAR);
				longest = 0;
				/* match the longest or shortest suffix */
				if (*sub == '#')
					longest = 1, sub++;
				/* perform the match */
				if ((len = match_prefix(sub, p, longest)) == 0)
					return (p);
				/* return the match */
				p2 = my_malloc(&shell.memory, strlen(p) - len + 1);
				if (p2)
					strcpy(p2, p + len);
				free(p);
				return (p2);
			default: /* unknown operator */
				return INVALID_VAR;
			}
		}
		/* no substitution clause. return the variable's original value */
	}
	/*
		* we have substituted the variable's value. now go POSIX style on it.
		*/
	expanded = 0;
	if (tmp)
	{
		if ((tmp = word_expand_to_str(tmp)))
			expanded = 1;
	}
	/* do we need to set new value to the variable? */
	if (setme)
	{
		/* if variable not defined, add it now */
		if (!entry)
			entry = add_to_symtab(var_name);
		/* and set its value */
		if (entry)
			symtab_entry_setval(entry, tmp);
	}
	p = NULL;
	if (get_length)
	{
		if (!tmp)
			sprintf(buf, "0");
		else
			sprintf(buf, "%lu", strlen(tmp));
		/* get a copy of the buffer */
		p = my_malloc(&shell.memory, strlen(buf) + 1);
		if (p)
			strcpy(p, buf);
	}
	else
	{
		/* "normal" variable value */
		p = my_malloc(&shell.memory, strlen(tmp) + 1);
		if (p)
			strcpy(p, tmp);
	}
	/* free the expanded word list */
	if (expanded)
		free(tmp);
	/* return the result */
	return p ?: INVALID_VAR;
}
