/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_subst_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 22:55:03 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/27 23:01:37 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_struct(t_cmdsubst *strct, char *orig_cmd)
{
	strct->bufsz = 0;
	strct->buf = NULL;
	strct->p = NULL;
	strct->i = 0;
	strct->fp = NULL;
	strct->backquoted = (*orig_cmd == '`');
}

char	*allocate_memory_for_cmd(t_cmdsubst *strct, char *orig_cmd)
{
	strct->cmd = malloc(ft_strlen(orig_cmd + 1));
	if (!strct->cmd)
	{
		fprintf(stderr,
			"error: insufficient memory to perform command substitution\n");
		return (NULL);
	}
	return (strct->cmd);
}

char	*handle_backquoted_status(t_cmdsubst *strct, char *orig_cmd, char *cmd2)
{
	if (strct->backquoted)
		ft_strcpy(strct->cmd, orig_cmd + 1);
	else
		ft_strcpy(strct->cmd, orig_cmd + 2);
	cmd2 = strct->cmd;
	return (cmd2);
}

void	special_character_replacement(t_cmdsubst *strct)
{
	strct->p2 = strct->p1;
	strct->p3 = strct->p1 + 1;
	while (true)
	{
		*strct->p2 = *strct->p3;
		if (!(*strct->p2))
			break ;
		strct->p2++;
		strct->p3++;
	}
}

void	handle_special_characters(t_cmdsubst *strct)
{
	strct->cmdlen = ft_strlen(strct->cmd);
	if (strct->backquoted)
	{
		if (strct->cmd[strct->cmdlen - 1] == '`')
			strct->cmd[strct->cmdlen - 1] = '\0';
		strct->p1 = strct->cmd;
		while (*strct->p1)
		{
			if (*strct->p1 == '\\' && (strct->p1[1] == '$'
					|| strct->p1[1] == '`' || strct->p1[1] == '\\'))
			{
				special_character_replacement(strct);
			}
			strct->p1++;
		}
	}
	else
	{
		if (strct->cmd[strct->cmdlen - 1] == ')')
			strct->cmd[strct->cmdlen - 1] = '\0';
	}
}
