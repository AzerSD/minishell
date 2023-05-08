/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_substitution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:17:07 by asioud            #+#    #+#             */
/*   Updated: 2023/03/30 17:17:07 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

/**
 * @brief perform command substitutions.
 * the backquoted flag tells if we are called from a backquoted command substitution:
 * `command` or a regular one: $(command)
*/
char	*command_substitute(char *orig_cmd)
{
	char	b[1024];
	size_t	bufsz;
	char	*buf;
	char	*p;
	int		i;
	int		backquoted;
	char	*cmd;
	size_t	cmdlen;
	char	*p1;
	char	*p2;
	char	*p3;
	FILE	*fp = NULL;
	char	*buf2;

	bufsz = 0;
	buf = NULL;
	p = NULL;
	i = 0;
	backquoted = (*orig_cmd == '`');
	/*
		* fix cmd in the backquoted version.. we skip the first char (if using the
		* old, backquoted version),
		or the first two chars (if using the POSIX version).
	*/
	cmd = malloc(strlen(orig_cmd + 1));
	if (!cmd)
	{
		fprintf(stderr,
				"error: insufficient memory to perform command substitution\n");
		return NULL;
	}
	strcpy(cmd, orig_cmd + (backquoted ? 1 : 2));
	char *cmd2 = cmd;
	cmdlen = strlen(cmd);
	if (backquoted)
	{
		/* remove the last back quote */
		if (cmd[cmdlen - 1] == '`')
			cmd[cmdlen - 1] = '\0';
		/* fix the backslash-escaped chars */
		p1 = cmd;
		do
		{
			if (*p1 == '\\' &&
				(p1[1] == '$' || p1[1] == '`' || p1[1] == '\\'))
			{
				p2 = p1;
				p3 = p1 + 1;
				while ((*p2++ = *p3++))
					;
			}
		} while (*(++p1));
	}
	else
	{
		/* remove the last closing brace */
		if (cmd[cmdlen - 1] == ')')
			cmd[cmdlen - 1] = '\0';
	}
	fp = popen(cmd2, "r");
	/* check if we have opened the pipe */
	if (!fp)
	{
		free(cmd2);
		fprintf(stderr, "error: failed to open pipe: %s\n", strerror(errno));
		return NULL;
	}
	/* read the command output */
	while ((i = fread(b, 1, 1024, fp)))
	{
		/* first time. alloc buffer */
		if (!buf)
		{
			buf = malloc(i + 1);
			if (!buf)
				goto fin;
			p = buf;
		}
		/* extend buffer */
		else
		{
			buf2 = realloc(buf, bufsz + i + 1);
			if (!buf2)
			{
				free(buf);
				buf = NULL;
				goto fin;
			}
			buf = buf2;
			p = buf + bufsz;
		}
		bufsz += i;
		/* copy the input and add the null terminating byte */
		memcpy(p, b, i);
		p[i] = '\0';
	}
	if (!bufsz)
	{
		free(cmd2);
		return NULL;
	}
	/* now remove any trailing newlines */
	i = bufsz - 1;
	while (buf[i] == '\n' || buf[i] == '\r')
	{
		buf[i] = '\0';
		i--;
	}
fin:
	pclose(fp);
	free(cmd2);
	if (!buf)
		fprintf(stderr,
				"error: insufficient memory to perform command substitution\n");
	return buf;
}
