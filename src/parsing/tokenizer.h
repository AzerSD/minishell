/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 01:58:31 by asioud            #+#    #+#             */
/*   Updated: 2023/07/03 20:16:05 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H
# define EOF_TOKEN NULL

typedef enum e_token_type
{
	PARSE_DEFAULT,
	PARSE_ASSIGNMENT,
	TOKEN_PIPE,
	TOKEN_EOF,
	TOKEN_OUTPUT,
	TOKEN_INPUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_FILE,
}					t_token_type;

/**
 * @brief Structure to hold the current token
 * @param tok_buff			Pointer to the token buffer
 * @param tok_buff_size		Size of the token buffer
 * @param tok_buff_index	Index of the token buffer (it tells us where to 
 * 							add the next input character in the buffer)
 * @param t_token_type		Current parse state
*/
typedef struct s_curr_tok
{
	char			*tok_buff;
	int				tok_buff_size;
	int				tok_buff_index;
	t_token_type	tok_type;
}					t_curr_tok;

/**
 * @brief 	Structure to hold one token at a time
 * @param cli		Pointer to the cli
 * @param text		Pointer to the token text
 * @param text_len	Length of token text
*/
typedef struct s_token
{
	t_cli			*cli;
	char			*text;
	int				text_len;
	t_token_type	tok_type;
}					t_token;

/**
 * @brief Retrieves the next token from the given CLI input.
 * @param cli A pointer to t_cli which contains the CLI input information.
 * @param curr A pointer to t_curr_tok, to store the current token information.
 * @return A pointer to a t_token representing the next token, 
 * 			or EOF_TOKEN if the end of input is reached or an error occurs.
*/
t_token				*get_token(t_cli *cli, t_curr_tok *curr);

void				init_curr_tok(t_curr_tok *curr);

/**
 * @brief free the memory used by a token structure
*/
void				free_token(t_token *tok);

void				add_to_buf(char c, t_curr_tok *curr);
void				handle_pipe(t_cli *cli, t_curr_tok *curr, int *endloop);
void				handle_equals_sign(t_curr_tok *curr);
void				handle_newline(t_cli *cli, t_curr_tok *curr, int *endloop);
void				handle_whitespace(t_curr_tok *curr, int *endloop);
void				*handle_dollar_sign(t_cli *cli, t_curr_tok *curr);
void				handle_backslash(t_cli *cli, t_curr_tok *curr);
void				*handle_quotes(t_cli *cli, t_curr_tok *curr, char nc);
void				handle_redirection(t_cli *cli, t_curr_tok *curr,
						int *endloop, char nc);
int					is_valid_variable_name(const char *str);
t_node				*p_heredoc(t_token *tok, t_cli *cli, \
	t_curr_tok *curr, t_node *ptr);
enum e_node_type	get_node_type(t_token_type state);

#endif
