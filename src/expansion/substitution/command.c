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

#include "minishell.h"

FILE	*pipe_command(char *cmd)
{
	FILE	*fp;

	fp = popen(cmd, "r");
	return (fp);
}

char	*read_from_pipe(FILE *fp, char *b, size_t *bufsz, char **p)
{
	int		i;
	char	*buf;

	i = fread(b, 1, 1024, fp);
	while (i)
	{
		if (!buf)
		{
			buf = my_malloc(&g_shell.memory, i + 1);
			if (!buf)
				return (buf);
			*p = buf;
		}
		else
		{
			buf = extend_buffer(buf, *bufsz, i);
			*p = buf + *bufsz;
		}
		*bufsz += i;
		ft_memcpy(*p, b, i);
		(*p)[i] = '\0';
		i = fread(b, 1, 1024, fp);
	}
	return (buf);
}

FILE	*prepare_command_and_open_pipe(char *orig_cmd, char **cmd_ptr)
{
	char	*cmd;
	size_t	cmdlen;
	FILE	*fp;

	fp = NULL;
	cmd = fix_cmd(orig_cmd, *orig_cmd == '`');
	if (!cmd)
		return (NULL);
	cmdlen = ft_strlen(cmd);
	if (*orig_cmd == '`')
		fix_backquoted_cmd(cmd, cmdlen);
	else
		remove_closing_brace(cmd, cmdlen);
	fp = pipe_command(cmd);
	*cmd_ptr = cmd;
	return (fp);
}

char	*read_and_cleanup_pipe(FILE *fp, char *cmd)
{
	char	b[1024];
	size_t	bufsz;
	char	*buf;
	char	*p;

	buf = NULL;
	if (!fp)
	{
		ft_printf_fd(STDERR_FILENO, "error: %s: %s\n", "failed to open pipe",
			strerror(errno));
		return (NULL);
	}
	buf = read_from_pipe(fp, b, &bufsz, &p);
	if (!bufsz)
	{
		free(cmd);
		return (NULL);
	}
	remove_trailing_newlines(buf, bufsz);
	pclose(fp);
	free(cmd);
	if (!buf)
		ft_printf_fd(STDERR_FILENO, "error: %s: %s\n", \
		"insufficient memory to perform command substitution", strerror(errno));
	return (buf);
}

char	*command_substitute(char *orig_cmd)
{
	char	*cmd;
	FILE	*fp;

	cmd = NULL;
	fp = prepare_command_and_open_pipe(orig_cmd, &cmd);
	return (read_and_cleanup_pipe(fp, cmd));
}
