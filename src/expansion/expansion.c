/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:05:17 by asioud            #+#    #+#             */
/*   Updated: 2023/06/18 14:18:25 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_word	*expand(char *orig_word)
{
	char			*pstart;
	char			*p;
	char			*p2;
	size_t			i;
	size_t			len;
	int				in_double_quotes;
	int				in_var_assign;
	int				var_assign_eq;
	int				expanded;
	int				tilde_quoted;
	int				endme;
	struct s_word	*words;
	char			*tmp;
	char			c;
	char *(*func)(char *);

	if (!orig_word)
		return NULL;
	if (!*orig_word)
		return make_word(orig_word);
	pstart = malloc(strlen(orig_word) + 1);
	if (!pstart)
		return NULL;
	strcpy(pstart, orig_word);
	p = pstart;
	i = 0;
	in_double_quotes = 0;
	in_var_assign = 0;
	var_assign_eq = 0;
	expanded = 0;
	do
	{
		switch (*p)
		{
		case '~':
			/* don't perform tilde expansion inside double quotes */
			if (in_double_quotes)
				break ;
			/* expand a tilde prefix only if:
				* - it is the first unquoted char in the string.
				* - it is part of a variable assignment,
					and is preceded by the first
				*   equals sign or a colon.
				*/
			if (p == pstart || (in_var_assign && (p[-1] == ':' || (p[-1] == '='
							&& var_assign_eq == 1))))
			{
				/* find the end of the tilde prefix */
				tilde_quoted = 0;
				endme = 0;
				p2 = p + 1;
				while (*p2)
				{
					switch (*p2)
					{
					case '\\':
						tilde_quoted = 1;
						p2++;
						break ;
					case '"':
					case '\'':
						i = find_closing_quote(p2);
						if (i)
						{
							tilde_quoted = 1;
							p2 += i;
						}
						break ;
					case '/':
						endme = 1;
						break ;
					case ':':
						if (in_var_assign)
							endme = 1;
						break ;
					}
					if (endme)
						break ;
					p2++;
				}
				/* if any part of the prefix is quoted, no expansion is done */
				if (tilde_quoted)
				{
					/* just skip the tilde prefix */
					p = p2;
					break ;
				}
				/* otherwise, extract the prefix */
				len = p2 - p;
				substitute_word(&pstart, &p, len, tilde_expansion,
						!in_double_quotes);
				expanded = 1;
			}
			break ;
		case '"':
			/* toggle quote mode */
			in_double_quotes = !in_double_quotes;
			break ;
		case '=':
			/* skip it if inside double quotes */
			if (in_double_quotes)
				break ;
			/* check the previous string is a valid var name */
			len = p - pstart;
			tmp = malloc(len + 1);
			if (!tmp)
			{
				fprintf(stderr,
						"error: insufficient memory for internal buffers\n");
				break ;
			}
			strncpy(tmp, pstart, len);
			tmp[len] = '\0';
			/*
				* if the string before '=' is a valid var name,
				we have a variable
				* assignment.. we set in_var_assign to indicate that, and we set
				* var_assign_eq which indicates this is the first equals sign (we use
				* this when performing tilde expansion -- see code above).
				*/
			if (is_name(tmp))
			{
				in_var_assign = 1;
				var_assign_eq++;
			}
			free(tmp);
			break ;
		case '\\':
			/* skip backslash (we'll remove it later on) */
			p++;
			break ;
		case '\'':
			/* if inside double quotes,
				treat the single quote as a normal char */
			if (in_double_quotes)
			{
				break ;
			}
			/* skip everything, up to the closing single quote */
			p += find_closing_quote(p);
			break ;
		case '`':
			/* find the closing back quote */
			if ((len = find_closing_quote(p)) == 0)
			{
				/* not found. bail out */
				break ;
			}
			/* otherwise, extract the command and substitute its output */
			substitute_word(&pstart, &p, len + 1, command_substitute, 0);
			expanded = 1;
			break ;
		/*
			* the $ sign might introduce:
			* - parameter expansions: ${var} or $var
			* - command substitutions: $()
			* - arithmetic expansions: $(())
			* - environment variable that should expand to its value
			*exp bash-3.2$ $USER
				bash: lhasmi: command not found  DONE
			*    When you type $? and hit enter, bash interprets this as a command to be executed.
Before executing, bash performs variable substitution.
It replaces $? with the exit code of the last command executed in the shell.
Bash then tries to execute the command 127.
Since there is no command named 127, it prints an error message bash: 127: command not found.
			*/
		case '$':
			c = p[1];
			switch (c)
			{
			// case '?':
				/* interpret this as a command to be executed */

				/*
				Before executing, minishell performs variable substitution.
				It replaces $? with the exit code of the last command executed in the shell.
			*/
			/*

			*/
			case '{':
				/* find the closing quote */
				if ((len = find_closing_brace(p + 1)) == 0)
				{
					/* not found. bail out */
					break ;
				}
				/*
					*  calling var_expand() might return an INVALID_VAR result which
					*  makes the following call fail.
					*/
				if (!substitute_word(&pstart, &p, len + 2, var_expand, 0))
				{
					free(pstart);
					return NULL;
				}
				expanded = 1;
				break ;
			/*
				* arithmetic expansion $(()) or command substitution $().
				*/
			case '(':
				/* check if we have one or two opening braces */
				i = 0;
				if (p[2] == '(')
					i++;
				/* find the closing quote */
				if ((len = find_closing_brace(p + 1)) == 0)
					/* not found. bail out */
					break ;
				/*
					* otherwise,
						extract the expression and substitute its value.
					* if we have one brace (i == 0),
						we'll perform command substitution.
					* otherwise, arithmetic expansion.
					*/
				// func = i ? arithm_expand : command_substitute;
				func = command_substitute;
				substitute_word(&pstart, &p, len + 2, func, 0);
				expanded = 1;
				break ;
		default:
			/* var names must start with an alphabetic char or _ */
			if (!isalpha(p[1]) && p[1] != '_')
				break ;
			p2 = p + 1;
			/* get the end of the var name */
			while (*p2)
			{
				if (!isalnum(*p2) && *p2 != '_')
					break ;
				p2++;
			}
			/* empty name */
			if (p2 == p + 1)
				break ;
			/* perform variable expansion */
			substitute_word(&pstart, &p, p2 - p, var_expand, 0);
			expanded = 1;
			break ;
		}
		break ;

		default:
			if (isspace(*p) && !in_double_quotes)
				expanded = 1;
			break ;
		}
	} while (*(++p));
	/* if we performed word expansion, do field splitting */
	words = NULL;
	if (expanded)
		words = field_split(pstart);
	/* no expansion done, or no field splitting done */
	if (!words)
	{
		words = make_word(pstart);
		/* error making word struct */
		if (!words)
		{
			fprintf(stderr, "error: insufficient memory\n");
			free(pstart);
			return NULL;
		}
	}
	free(pstart);
	/* perform pathname expansion and quote removal */
	words = pathnames_expand(words);
	remove_quotes(words);
	/* return the expanded list */
	return words;
}


/**
 * @brief check if char c is a valid $IFS character.
 * @returns 1 if char c is an $IFS character, 0 otherwise.
*/
static inline int	is_IFS_char(char c, char *IFS)
{
	if (!*IFS)
		return 0;
	do
	{
		if (c == *IFS)
			return 1;
	} while (*++IFS);
	return 0;
}



void	skip_IFS_whitespace(char **str, char *IFS)
{
	char	*IFS2;
	char	*s2;

	IFS2 = IFS;
	s2 = *str;
	do
	{
		if (*s2 == *IFS2)
		{
			s2++;
			IFS2 = IFS - 1;
		}
	} while (*++IFS2);
	*str = s2;
}

void	skip_IFS_delim(char *str, char *IFS_space, char *IFS_delim, size_t *_i,
		size_t len)
{
	size_t	i;

	i = *_i;
	while ((i < len) && is_IFS_char(str[i], IFS_space))
		i++;
	while ((i < len) && is_IFS_char(str[i], IFS_delim))
		i++;
	while ((i < len) && is_IFS_char(str[i], IFS_space))
		i++;
	*_i = i;
}

struct s_word	*field_split(char *str)
{
	struct s_symtab_entry	*entry;
	char					*IFS;
	char					*p;
	char					IFS_space[64];
	char					IFS_delim[64];
	char					*sp;
	char					*dp;
	size_t					len;
	size_t					i;
	size_t					j;
	size_t					k;
	int						fields;
	char					quote;
	struct s_word			*first_field;
	struct s_word			*cur;
	char					*tmp;
	struct s_word			*fld;

	entry = get_symtab_entry("IFS");
	IFS = entry ? entry->val : NULL;
	/* POSIX says no IFS means: "space/tab/NL" */
	if (!IFS)
	{
		IFS = " \t\n";
	}
	/* POSIX says empty IFS means no field splitting */
	if (IFS[0] == '\0')
	{
		return NULL;
	}
	/* get the IFS spaces and delimiters separately */
	if (strcmp(IFS, " \t\n") == 0) /* "standard" IFS */
	{
		IFS_space[0] = ' ';
		IFS_space[1] = '\t';
		IFS_space[2] = '\n';
		IFS_space[3] = '\0';
		IFS_delim[0] = '\0';
	}
	else /* "custom" IFS */
	{
		p = IFS;
		sp = IFS_space;
		dp = IFS_delim;
		do
		{
			if (isspace(*p))
				*sp++ = *p++;
			else
				*dp++ = *p++;
		} while (*p);
		*sp = '\0';
		*dp = '\0';
	}
	len = strlen(str);
	i = 0, j = 0, k = 0;
	fields = 1;
	quote = 0;
	/* skip any leading whitespaces in the string */
	skip_IFS_whitespace(&str, IFS_space);
	/* estimate the needed number of fields */
	do
	{
		switch (str[i])
		{
		/* skip escaped chars */
		case '\\':
			/* backslash has no effect inside single quotes */
			if (quote != '\'')
				i++;
			break ;
		/* don't count whitespaces inside quotes */
		case '\'':
		case '"':
		case '`':
			if (quote == str[i])
				quote = 0;
			else
				quote = str[i];
			break ;
		default:
			/* skip normal characters if we're inside quotes */
			if (quote)
				break ;
			if (is_IFS_char(str[i], IFS_space) || is_IFS_char(str[i],
					IFS_delim))
			{
				skip_IFS_delim(str, IFS_space, IFS_delim, &i, len);
				if (i < len)
					fields++;
			}
			break ;
		}
	} while (++i < len);
	/* we have only one field. no field splitting needed */
	if (fields == 1)
		return NULL;
	first_field = NULL;
	cur = NULL;
	/* create the fields */
	i = 0;
	j = 0;
	quote = 0;
	do
	{
		switch (str[i])
		{
		/* skip escaped chars */
		case '\\':
			/* backslash has no effect inside single quotes */
			if (quote != '\'')
				i++;
			break ;
		/* skip single quoted substrings */
		case '\'':
			p = str + i + 1;
			while (*p && *p != '\'')
				p++;
			i = p - str;
			break ;
		/* remember if we're inside/outside double and back quotes */
		case '"':
		case '`':
			if (quote == str[i])
				quote = 0;
			else
				quote = str[i];
			break ;
		default:
			/* skip normal characters if we're inside quotes */
			if (quote)
				break ;
			/*
				* delimit the field if we have an IFS space or delimiter char,
					or if
				* we reached the end of the input string.
				*/
			if (is_IFS_char(str[i], IFS_space) ||
				is_IFS_char(str[i], IFS_delim) || (i == len))
			{
				/* copy the field text */
				tmp = malloc(i - j + 1);
				if (!tmp)
				{
					fprintf(stderr,
							"error: insufficient memory for field splitting\n");
					return first_field;
				}
				strncpy(tmp, str + j, i - j);
				tmp[i - j] = '\0';
				/* create a new struct for the field */
				fld = malloc(sizeof(struct s_word));
				if (!fld)
				{
					free(tmp);
					return first_field;
				}
				fld->data = tmp;
				fld->len = i - j;
				fld->next = NULL;
				if (!first_field)
					first_field = fld;
				if (!cur)
					cur = fld;
				else
				{
					cur->next = fld;
					cur = fld;
				}
				k = i;
				/* skip trailing IFS spaces/delimiters */
				skip_IFS_delim(str, IFS_space, IFS_delim, &i, len);
				j = i;
				if (i != k && i < len)
					i--; /* go back one step so the loop will work correctly */
			}
			break ;
		}
	} while (++i <= len);
	return first_field;
}

char	*word_expand_to_str(char *word)
{
	struct s_word	*w;
	char			*res;

	w = expand(word);
	if (!w)
		return NULL;
	res = wordlist_to_str(w);
	free_all_words(w);
	return res;
}


struct s_word	*make_word(char *str)
{
	struct s_word	*word;
	size_t			len;
	char			*data;

	word = malloc(sizeof(struct s_word));
	if (!word)
		return (NULL);
	len = strlen(str);
	data = malloc(len + 1);
	if (!data)
	{
		free(word);
		return (NULL);
	}
	strcpy(data, str);
	word->data = data;
	word->len = len;
	word->next = NULL;
	return (word);
}

void	free_all_words(struct s_word *first)
{
	struct s_word	*del;

	while (first)
	{
		del = first;
		first = first->next;
		if (del->data)
			free(del->data);
		free(del);
	}
}
