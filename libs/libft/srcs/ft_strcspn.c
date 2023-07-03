/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 04:17:37 by asioud            #+#    #+#             */
/*   Updated: 2023/07/03 04:17:49 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strcspn(const char *s, const char *charset)
{
	size_t	count;

	count = 0;
	while (ft_strchr(charset, *s++) == 0)
		count++;
	return (count);
}
