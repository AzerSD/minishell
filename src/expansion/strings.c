/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:07:23 by asioud            #+#    #+#             */
/*   Updated: 2023/03/30 19:07:23 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strchr_any(char *string, char *chars)
{
	char	*s;
	char	*c;

	if (!string || !chars)
		return (NULL);
	s = string;
	while (*s)
	{
		c = chars;
		while (*c)
		{
			if (*s == *c)
				return (s);
			c++;
		}
		s++;
	}
	return (NULL);
}

// function to calculate the extra length needed for the resultant string
size_t	count_extra_chars(char *v)
{
	size_t	len;

	len = 0;
	while (*v)
	{
		if (*v == '\\' || *v == '`' || *v == '$' || *v == '"')
			len++;
		v++;
	}
	return (len);
}

void	copy_and_escape(char *v, char *p)
{
	while (*v)
	{
		if (*v == '\\' || *v == '`' || *v == '$' || *v == '"')
		{
			*p++ = '\\';
			*p++ = *v++;
		}
		else
		{
			*p++ = *v++;
		}
	}
	*p = '\0';
}

size_t	calculate_length(char *val, int add_quotes)
{
	size_t	len;

	if (!val || !*val)
	{
		if (add_quotes)
			len = 3;
		else
			len = 1;
		return (len);
	}
	len = count_extra_chars(val);
	len += ft_strlen(val);
	if (add_quotes)
		len += 2;
	return (len);
}

char	*quote_val(char *val, int add_quotes)
{
	char	*res;
	size_t	len;
	char	*p;

	len = calculate_length(val, add_quotes);
	res = my_malloc(&g_shell.memory, len + 1);
	if (!val || !*val)
	{
		if (add_quotes)
			ft_strcpy(res, "\"\"");
		else
			ft_strcpy(res, "");
		return (res);
	}
	p = res;
	if (add_quotes)
		*p++ = '"';
	copy_and_escape(val, p);
	if (add_quotes)
	{
		p = p + ft_strlen(p);
		*p++ = '"';
		*p = '\0';
	}
	return (res);
}
