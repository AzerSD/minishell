/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:28:12 by asioud            #+#    #+#             */
/*   Updated: 2023/03/30 17:28:12 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# define INVALID_VAR ((char *)-1)

/**
 * @brief A word is a string of characters delimited by spaces.
 * @param data the string representing this word.
 * @param len the length of the string.
 * @param next a pointer to the next word or null for last word
*/
struct s_word
{
	char			*data;
	int				len;
	struct s_word	*next;
};

/**
 * @brief perform word expansion on a single word, pointed to by orig_word.

	* @returns the head of the linked list of the expanded fields and
	stores the last field
 * in the tail pointer.
*/
struct s_word	*expand(char *orig_word);

/**
 * @brief A simple shortcut to perform word-expansions on a string,
 * @returns the result as a string.
*/
char			*word_expand_to_str(char *word);
char			*var_expand(char *orig_var_name);

/**
 * @brief convert the string *word to a cmd_token struct,
 * so it can be passed to functions such as word_expand().
 * @param *str the string to convert.
 * @returns the malloc'd cmd_token struct, or NULL if insufficient memory.
*/
struct s_word	*make_word(char *str);

/**
 * @brief free the memory used by a list of words.
 * @param *first the first word in the list.
*/
void			free_all_words(struct s_word *first);

char			**get_filename_matches(char *pattern, glob_t *matches);
int				has_glob_chars(char *p, size_t len);
int				match_prefix(char *pattern, char *str, int longest);
int				match_suffix(char *pattern, char *str, int longest);

char			*command_substitute(char *orig_cmd);
void			remove_quotes(struct s_word *wordlist);
size_t			find_closing_quote(char *data);
size_t			find_closing_brace(char *data);

char			*tilde_expansion(char *s);

struct s_word	*pathnames_expand(struct s_word *words);

char			*wordlist_to_str(struct s_word *word);
void			delete_char_at(char *str, size_t index);
int				is_name(char *str);
char			*substitute_str(char *s1, char *s2, size_t start, size_t end);
int				substitute_word(char **pstart, char **p, size_t len, \
				char *(func)(char *), int add_quotes);

int				check_buffer_bounds(int *count, int *len, char ***buf);
char			*strchr_any(char *string, char *chars);
char			*quote_val(char *val, int add_quotes);
void			free_buffer(int len, char **buf);

#endif