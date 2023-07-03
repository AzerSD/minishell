/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 04:14:00 by asioud            #+#    #+#             */
/*   Updated: 2023/07/03 17:38:47 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strtok(char *str, const char *sep)
{
	static char	*p;

	p = 0;
	if (str)
		p = str;
	else if (!p)
		return (0);
	str = p + ft_strspn(p, sep);
	p = str + ft_strcspn(str, sep);
	if (p == str)
		return (p = 0);
	if (*p)
	{
		*p = 0;
		p += 1;
	}
	else
		p = 0;
	return (str);
}
