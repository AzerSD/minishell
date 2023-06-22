/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 16:05:17 by asioud            #+#    #+#             */
/*   Updated: 2023/06/23 01:00:28 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


struct s_word *make_word_if(struct s_word *words, char *pstart){

        words = make_word(pstart);
        if (!words)
        {
            fprintf(stderr, "error: insufficient memory\n");
            free(pstart);
            return NULL;
        }
    return words;
}

void check_double_quotes(char **p, int *in_double_quotes){
    if (**p == '"') {
        *in_double_quotes = !(*in_double_quotes);
        (*p)++;
    }
}

void check_backslash(char **p){
    if (**p == '\\') {
        (*p)++;
    }
}

void check_single_quotes(char **p, int in_double_quotes){
    if (**p == '\'' && !in_double_quotes) {
        *p += find_closing_quote(*p);
    }
}

void check_backtick(char **pstart, char **p){
    size_t len;
    if (**p == '`') {
        if ((len = find_closing_quote(*p)) != 0) {
            substitute_word(pstart, p, len + 1, command_substitute, 0);
        }
    }
}

void check_dollar_sign(char **pstart, char **p){
    char c, *p2;
    if (**p == '$') {
        c = (*p)[1];
        if (c == '?') {
            substitute_word(pstart, p, 2, var_expand, 0);
        } else {
            if (!isalpha((*p)[1]) && (*p)[1] != '_') {
                return;
            }
            p2 = *p + 1;
            while (*p2) {
                if (!isalnum(*p2) && *p2 != '_')
                    break;
                p2++;
            }
            if (p2 == *p + 1) {
                return;
            }
            substitute_word(pstart, p, p2 - *p, var_expand, 0);
        }
    }
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

void handle_tilde(char **pstart, char **p, char *endme, char *tilde_quoted, int *in_double_quotes, int *in_var_assign, int *var_assign_eq, int *expanded) {
    char *p2;
    size_t len, i;

    if (**p == '~' && !(*in_double_quotes)) {
        if (*p == *pstart || (*in_var_assign && ((*p)[-1] == ':' || ((*p)[-1] == '=' && *var_assign_eq == 1)))) {
            *tilde_quoted = 0;
            *endme = 0;
            p2 = *p + 1;
            while (*p2) {
                if (*p2 == '\\') {
                    *tilde_quoted = 1;
                    p2++;
                } else if (*p2 == '"' || *p2 == '\'') {
                    i = find_closing_quote(p2);
                    if (i) {
                        *tilde_quoted = 1;
                        p2 += i;
                    }
                } else if (*p2 == '/') {
                    *endme = 1;
                } else if (*p2 == ':' && *in_var_assign) {
                    *endme = 1;
                }

                if (*endme) {
                    break;
                }
                p2++;
            }
            
            if (*tilde_quoted) {
                *p = p2;
            } else {
                len = p2 - *p;
                substitute_word(pstart, p, len, tilde_expansion, !*in_double_quotes);
                *expanded = 1;
            }
        }
    }
}

void handle_equal(char **p, char **pstart, int *in_double_quotes, int *in_var_assign, int *var_assign_eq) {
    size_t len;
    char *tmp;

    if (**p == '=' && !(*in_double_quotes)) {
        len = *p - *pstart;
        tmp = malloc(len + 1);
        if (!tmp) {
            fprintf(stderr, "error: insufficient memory for internal buffers\n");
            return;
        }
        strncpy(tmp, *pstart, len);
        tmp[len] = '\0';
        if (is_name(tmp)) {
            *in_var_assign = 1;
            (*var_assign_eq)++;
        }
        free(tmp);
    }
}

void handle_brace_dollar(char **pstart, char **p, int *expanded) {
    size_t len;
    char c, *(*func)(char *);
    int i;

    if ((*p)[0] == '$' && (*p)[1] == '{') {
        if ((len = find_closing_brace(*p + 1)) == 0) {
            return;
        }

        if (!substitute_word(pstart, p, len + 2, var_expand, 0)) {
            free(*pstart);
            *pstart = NULL;
            return;
        }
        *expanded = 1;
    } else if ((*p)[0] == '$' && (*p)[1] == '(') {
        i = 0;
        if ((*p)[2] == '(') {
            i++;
        }

        if ((len = find_closing_brace(*p + 1)) == 0) {
            return;
        }

        func = command_substitute;
        substitute_word(pstart, p, len + 2, func, 0);
        *expanded = 1;
    }
}

struct s_word *expand(char *orig_word) {
    char *pstart, *p, *p2, c, *(*func)(char *);
    size_t i, len;
    int in_double_quotes = 0, in_var_assign = 0, var_assign_eq = 0, expanded = 0, tilde_quoted = 0, endme = 0;
    struct s_word *words;

    if (!orig_word) return NULL;
    if (!*orig_word) return make_word(orig_word);

    pstart = malloc(strlen(orig_word) + 1);
    if (!pstart) return NULL;
    strcpy(pstart, orig_word);
    p = pstart;

    while (*p) {
        handle_tilde(&pstart, &p, &endme, &tilde_quoted, &in_double_quotes, &in_var_assign, &var_assign_eq, &expanded);
        if (*p == '"') in_double_quotes = !in_double_quotes;
        handle_equal(&p, &pstart, &in_double_quotes, &in_var_assign, &var_assign_eq);
        if (*p == '\\') p++;
        if (*p == '\'' && !in_double_quotes) p += find_closing_quote(p);
        if (*p == '`') {
            if ((len = find_closing_quote(p)) != 0) {
                substitute_word(&pstart, &p, len + 1, command_substitute, 0);
                expanded = 1;
            }
        }
        handle_brace_dollar(&pstart, &p, &expanded);
        if (*p == '$' && (isalpha(p[1]) || p[1] == '_')) {
            p2 = p + 1;
            while (*p2 && (isalnum(*p2) || *p2 == '_')) p2++;
            if (p2 != p + 1) {
                substitute_word(&pstart, &p, p2 - p, var_expand, 0);
                expanded = 1;
            }
        }
        if (isspace(*p) && !in_double_quotes) expanded = 1;
        p++;
    }

    words = NULL;
    if (!words) {
        words = make_word(pstart);
        if (!words) {
            fprintf(stderr, "error: insufficient memory\n");
            free(pstart);
            return NULL;
        }
    }
    free(pstart);
    words = pathnames_expand(words);
    remove_quotes(words);
    return words;
}
