/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 04:15:42 by asioud            #+#    #+#             */
/*   Updated: 2023/07/03 04:15:59 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strspn(const char *s1, const char *s2)
{
	size_t	counter;

	counter = 0;
	while (*s1 && ft_strchr(s2, *s1++))
		counter++;
	return (counter);
}
