/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 01:54:40 by asioud            #+#    #+#             */
/*   Updated: 2023/07/27 16:26:27 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt_display_ps1(void)
{
	struct s_symtab_entry	*entry;

	entry = get_symtab_entry("PS1");
	if (entry && entry->val)
		fprintf(stderr, "%s", entry->val);
	else
		fprintf(stderr, "\033[1;32m$ ");
}

void	prompt_display_ps2(void)
{
	struct s_symtab_entry	*entry;

	entry = get_symtab_entry("PS2");
	if (entry && entry->val)
		fprintf(stderr, "%s", entry->val);
	else
		fprintf(stderr, "\033[1;32m> ");
}
