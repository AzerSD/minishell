/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 04:31:14 by asioud            #+#    #+#             */
/*   Updated: 2023/07/03 04:31:35 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char	*dest;
	size_t	n;

	dest = dst;
	n = 0;
	while (n < len && src[n] != '\0')
	{
		dst[n] = src[n];
		n++;
	}
	while (n < len)
		dst[n++] = '\0';
	return (dst);
}
