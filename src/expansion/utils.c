/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 19:45:51 by asioud            #+#    #+#             */
/*   Updated: 2023/07/02 19:46:09 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_buffer_bounds(int *count, int *len, char ***buf)
{
	int		newlen;
	char	**hn2;

	if (*count >= *len)
	{
		if (!(*buf))
		{
			*buf = my_malloc(&shell.memory, 32 * sizeof(char **));
			if (!(*buf))
				return (0);
			*len = 32;
		}
		else
		{
			newlen = (*len) * 2;
			hn2 = realloc(*buf, newlen * sizeof(char **));
			if (!hn2)
				return (0);
			*buf = hn2;
			*len = newlen;
		}
	}
	return (1);
}

void	free_buffer(int len, char **buf)
{
	if (!len)
		return ;
	while (len--)
		free(buf[len]);
	free(buf);
}
