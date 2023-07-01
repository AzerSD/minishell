/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 15:09:50 by asioud            #+#    #+#             */
/*   Updated: 2023/07/01 15:55:13 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	substitute_word(char **pstart, char **p, size_t len, char *(func)(char *),
		int add_quotes)
{
	char *tmp;
	char *tmp2;
	size_t i;

	tmp = my_malloc(&shell.memory, len + 1);
	if (!tmp)
	{
		(*p) += len;
		return (0);
	}
	strncpy(tmp, *p, len);
	tmp[len--] = '\0';
	if (func)
	{
		tmp2 = func(tmp);
		if (tmp2 == INVALID_VAR)
			tmp2 = NULL;
		if (tmp2)
			free(tmp);
	}
	else
		tmp2 = tmp;
	if (!tmp2)
	{
		(*p) += len;
		free(tmp);
		return (0);
	}
	i = (*p) - (*pstart);
	tmp = quote_val(tmp2, add_quotes);
	free(tmp2);
	if (tmp)
	{
		tmp2 = substitute_str(*pstart, tmp, i, i + len);
		if (tmp2)
		{
			(*pstart) = tmp2;
			len = strlen(tmp);
		}
		free(tmp);
	}
	(*p) = (*pstart) + i + len - 1;
	return (1);
}
