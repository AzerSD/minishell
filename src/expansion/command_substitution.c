/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_substitution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2023/07/27 19:56:21 by lhasmi            #+#    #+#             */
/*   Updated: 2023/07/27 19:56:21 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

FILE	*open_pipe(t_cmdsubst *strct, char *cmd2)
{
	strct->fp = popen(cmd2, "r");
	if (!strct->fp)
	{
		free(cmd2);
		fprintf(stderr, "error: failed to open pipe: %s\n", strerror(errno));
		return (NULL);
	}
	return (strct->fp);
}

int	error_handling_for_buffer(t_cmdsubst *strct)
{
	strct->buf = malloc(strct->i + 1);
	if (!strct->buf)
	{
		fprintf(stderr,
			"error: insufficient memory to perform command substitution\n");
		return (-1);
	}
	strct->p = strct->buf;
	return (0);
}

int	read_from_pipe_and_store_into_buffer(FILE *fp, t_cmdsubst *strct, char *b)
{
	strct->i = fread(b, 1, 1024, fp);
	while (strct->i)
	{
		if (!strct->buf)
			return (error_handling_for_buffer(strct));
		else
		{
			strct->buf2 = realloc(strct->buf, strct->bufsz + strct->i + 1);
			if (!strct->buf2)
			{
				free(strct->buf);
				strct->buf = NULL;
				return (error_handling_for_buffer(strct));
			}
			strct->buf = strct->buf2;
			strct->p = strct->buf + strct->bufsz;
		}
		strct->bufsz += strct->i;
		ft_memcpy(strct->p, b, strct->i);
		strct->p[strct->i] = '\0';
	}
	return (0);
}

void	strip_trailing_newlines(t_cmdsubst *strct, char *cmd2)
{
	strct->i = strct->bufsz - 1;
	while (strct->buf[strct->i] == '\n' || strct->buf[strct->i] == '\r')
	{
		strct->buf[strct->i] = '\0';
		strct->i--;
	}
	pclose(strct->fp);
	free(cmd2);
	if (!strct->buf)
	{
		fprintf(stderr,
			"error: insufficient memory to perform command substitution\n");
		return ;
	}
}

char	*command_substitute(char *orig_cmd)
{
	t_cmdsubst	strct;
	char		*cmd2;
	char		b[1024];

	cmd2 = NULL;
	initialize_struct(&strct, orig_cmd);
	strct.cmd = allocate_memory_for_cmd(&strct, orig_cmd);
	cmd2 = handle_backquoted_status(&strct, orig_cmd, cmd2);
	handle_special_characters(&strct);
	strct.fp = open_pipe(&strct, cmd2);
	if (read_from_pipe_and_store_into_buffer(strct.fp, &strct, b) == -1)
	{
		pclose(strct.fp);
		free(cmd2);
		return (NULL);
	}
	if (!strct.bufsz)
	{
		free(cmd2);
		return (NULL);
	}
	strip_trailing_newlines(&strct, cmd2);
	return (strct.buf);
}
