
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

	i = 0;
	in_double_quotes = 0;
	in_var_assign = 0;
	var_assign_eq = 0;
	expanded = 0;
	words = NULL;
	char			*(*func)(char *);
	if (!orig_word)
		return (NULL);
	if (!*orig_word)
		return (make_word(orig_word));
	pstart = malloc(strlen(orig_word) + 1);
	if (!pstart)
		return (NULL);
	strcpy(pstart, orig_word);
	p = pstart;
	while (*p)
	{
		if (*p == '"')
		{
			in_double_quotes = !in_double_quotes;
		}
		else if (*p == '\\')
		{
			p++;
		}
		else if (*p == '\'')
		{
			if (!in_double_quotes)
				p += find_closing_quote(p);
		}
		else if (*p == '$')
		{
			c = p[1];
			if (c == '{')
			{
				if ((len = find_closing_brace(p + 1)) != 0)
				{
					if (!substitute_word(&pstart, &p, len + 2, var_expand, 0))
					{
						free(pstart);
						return (NULL);
					}
					expanded = 1;
				}
			}
			else if (c == '(')
			{
				i = 0;
				if (p[2] == '(')
					i++;
				if ((len = find_closing_brace(p + 1)) != 0)
				{
					func = command_substitute;
					substitute_word(&pstart, &p, len + 2, func, 0);
					expanded = 1;
				}
			}
			else if (isalpha(p[1]) || p[1] == '_')
			{
				p2 = p + 1;
				while (*p2)
				{
					if (!isalnum(*p2) && *p2 != '_')
						break ;
					p2++;
				}
				if (p2 != p + 1)
				{
					substitute_word(&pstart, &p, p2 - p, var_expand, 0);
					expanded = 1;
				}
			}
		}
		else if (isspace(*p) && !in_double_quotes)
		{
			expanded = 1;
		}
		p++;
	}
	if (!words)
		words = make_word(pstart);
	free(pstart);
	words = pathnames_expand(words);
	remove_quotes(words);
	return (words);
}
