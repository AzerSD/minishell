/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 00:48:44 by asioud            #+#    #+#             */
/*   Updated: 2023/07/01 00:52:54 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_node_content(t_node **child, char **str)
{
	if ((*child)->type == NODE_INPUT || (*child)->type == NODE_OUTPUT
		|| (*child)->type == NODE_APPEND || (*child)->type == NODE_HEREDOC)
	{
		*child = (*child)->next_sibling;
		return (1);
	}
	*str = (*child)->val.str;
	w = expand(str);
	if (!w)
		return (1);
}
