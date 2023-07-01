/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 01:58:21 by asioud            #+#    #+#             */
/*   Updated: 2023/07/01 02:59:53 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/**
 * @brief Parses a command from a sequence of tokens.
 * @param tok Representing the first token of the command.
 * @return A t_node representing the parsed command, or NULL if an error occurs.
 *
 * This function constructs a command node (t_node) by parsing the given
 * sequence of tokens. It iterates through the tokens, creating a child node for
 * each token and adding it to the command node. The function stops parsing when
 * it encounters a newline token or reaches the end of the input.
 * If an error occurs during parsing, the function returns NULL and frees any
 * allocated resources.
 */
t_node	*parse_cmd(struct s_token *tok, t_curr_tok *curr);
t_node	*parse_pipeline(t_token *tok, t_curr_tok *curr);
#endif
