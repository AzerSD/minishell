/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 04:31:14 by asioud            #+#    #+#             */
/*   Updated: 2023/07/30 19:13:34 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	n;

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
