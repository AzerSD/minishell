/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_randstring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:52:59 by asioud            #+#    #+#             */
/*   Updated: 2023/07/03 19:14:04 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_randstring(size_t length)
{
	char		*random_string;
	int			key;
	static char	*charset;
	size_t		n;

	charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHI\
		JKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
	random_string = NULL;
	if (length)
	{
		random_string = malloc(sizeof(char) * (length + 1));
		if (random_string)
		{
			n = 0;
			while (n < length)
			{
				key = rand() % (int)(sizeof(charset) - 1);
				random_string[n] = charset[key];
				n++;
			}
			random_string[length] = '\0';
		}
	}
	return (random_string);
}
