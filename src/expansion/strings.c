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
size_t count_extra_chars(char *v)
{
    size_t len = 0;
    while (*v)
    {
        if (*v == '\\' || *v == '`' || *v == '$' || *v == '"')
            len++;
        v++;
    }
    return len;
}

// function to copy characters from source to destination, adding escape character before specific characters
void copy_and_escape(char *v, char *p)
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

char *quote_val(char *val, int add_quotes)
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
    len = count_extra_chars(val);
    len += strlen(val);
    if (add_quotes)
        len += 2;
    res = my_malloc(&shell.memory, len + 1);
    if (!res)
        return (NULL);
    char *p = res;
    if (add_quotes)
        *p++ = '"';
    copy_and_escape(val, p);
    if (add_quotes)
    {
        p = p + strlen(p);
        *p++ = '"';
        *p = '\0';
    }
    return (res);
}


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
