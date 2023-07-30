/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:48:37 by asioud            #+#    #+#             */
/*   Updated: 2023/07/03 20:23:01 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fix_cmd(char *orig_cmd, int backquoted)
{
	char	*cmd;
	int		b;

	cmd = my_malloc(&g_shell.memory, ft_strlen(orig_cmd + 1));
	if (!cmd)
	{
		ft_printf_fd(STDERR_FILENO,
			"error: insufficient memory to perform command substitution\n");
		return (NULL);
	}
	if (backquoted)
		b = 1;
	else
		b = 2;
	ft_strcpy(cmd, orig_cmd + b);
	return (cmd);
}

void	fix_backquoted_cmd(char *cmd, size_t cmdlen)
{
	char	*p1;
	char	*p2;
	char	*p3;

	if (cmd[cmdlen - 1] == '`')
		cmd[cmdlen - 1] = '\0';
	p1 = cmd;
	while (*p1)
	{
		if (*p1 == '\\' && (p1[1] == '$' || p1[1] == '`' || p1[1] == '\\'))
		{
			p2 = p1;
			p3 = p1 + 1;
			while (*p2)
				*p2++ = *p3++;
		}
		p1++;
	}
}

void	remove_closing_brace(char *cmd, size_t cmdlen)
{
	if (cmd[cmdlen - 1] == ')')
		cmd[cmdlen - 1] = '\0';
}

char	*extend_buffer(char *buf, size_t bufsz, int i)
{
	char	*buf2;

	buf2 = ft_realloc(buf, bufsz + i + 1);
	if (!buf2)
	{
		free(buf);
		return (NULL);
	}
	buf = buf2;
	return (buf);
}

void	remove_trailing_newlines(char *buf, size_t bufsz)
{
	int	i;

	i = bufsz - 1;
	while (buf[i] == '\n' || buf[i] == '\r')
	{
		buf[i] = '\0';
		i--;
	}
}
