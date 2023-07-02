/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/03/30 19:07:23 by asioud            #+#    #+#             */
/*   Updated: 2023/03/30 19:07:23 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/**
 * @brief search string for any one of the passed characters.
 * @returns a char pointer to the first occurence of any of the characters,
 * NULL if none found.
*/
char	*strchr_any(char *string, char *chars)
{
	char	*s;
	char 	*c;

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

/**
 * @return the passed string value, quoted in a format that can
 * be used for reinput to the shell.
*/
char	*quote_val(char *val, int add_quotes)
{
	char *res = NULL;
	size_t len;
	/* empty string */
	if (!val || !*val)
	{
		len = add_quotes ? 3 : 1;
		res = my_malloc(&shell.memory, len);
		if (!res)
			return (NULL);
		strcpy(res, add_quotes ? "\"\"" : "");
		return (res);
	}
	len = 0;
	char *v = val, *p;
	while (*v)
	{
		switch (*v)
		{
		case '\\':
		case '`':
		case '$':
		case '"':
			len++;
			break ;
		}
		v++;
	}
	len += strlen(val);
	if (add_quotes)
		len += 2;
	res = my_malloc(&shell.memory, len + 1);
	if (!res)
		return (NULL);
	p = res;
	if (add_quotes)
		*p++ = '"';
	v = val;
	while (*v)
	{
		switch (*v)
		{
		case '\\':
		case '`':
		case '$':
		case '"':
			*p++ = '\\';
			*p++ = *v++;
			break ;

		default:
			*p++ = *v++;
			break ;
		}
	}
	if (add_quotes)
	{
		*p++ = '"';
	}
	*p = '\0';
	return (res);
}

/**
 * @brief alloc memory for,
	or extend the host (or user) names buffer if needed..
 * in the first call, the buffer is initialized to 32 entries.. subsequent
 * calls result in the buffer size doubling, so that it becomes 64, 128, ...
 * count is the number of used entries in the buffer, while len is the number
 * of alloc'd entries (size of buffer divided by sizeof(char **)).
 * @returns 1 if the buffer is alloc'd/extended, 0 otherwise.
*/
int	check_buffer_bounds(int *count, int *len, char ***buf)
{
	if (*count >= *len)
	{
		if (!(*buf))
		{
			/* first call. alloc memory for the buffer */
			*buf = my_malloc(&shell.memory, 32 * sizeof(char **));
			if (!(*buf))
				return (0);
			*len = 32;
		}
		else
		{
			/* subsequent calls. extend the buffer */
			int newlen = (*len) * 2;
			char **hn2 = realloc(*buf, newlen * sizeof(char **));
			if (!hn2)
				return (0);
			*buf = hn2;
			*len = newlen;
		}
	}
	return (1);
}

/**
 * @brief free the memory used to store the strings list pointed to by buf.
*/
void	free_buffer(int len, char **buf)
{
	if (!len)
		return ;
	while (len--)
		free(buf[len]);
	free(buf);
}
