/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 05:03:22 by asioud            #+#    #+#             */
/*   Updated: 2023/07/27 16:20:20 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	file_exists(char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISREG(st.st_mode))
		return (1);
	else
	{
		errno = ENOENT;
		return (0);
	}
}

static char	*build_path(char *start, char *end, char *file, int plen)
{
	char	*path;

	path = malloc(plen + 1 + strlen(file) + 1);
	if (!path)
		return (NULL);
	strncpy(path, start, plen);
	path[plen] = '\0';
	if (end[-1] != '/')
		strcat(path, "/");
	strcat(path, file);
	return (path);
}

char	*search_path(char *file)
{
	char	*path_env;
	char	*p;
	char	*p2;
	int		plen;
	char	*path;

	path_env = getenv("PATH");
	p = path_env;
	while (p && *p)
	{
		p2 = strchr(p, ':');
		if (!p2)
			p2 = p + strlen(p);
		plen = p2 - p;
		if (plen == 0)
			plen = 1;
		path = build_path(p, p2, file, plen);
		if (!path)
			return (NULL);
		if (file_exists(path))
			return (path);
		else
			free(path);
		if (*p2 == ':')
			p = p2 + 1;
		else
			p = NULL;
	}
	errno = ENOENT;
	return (NULL);
}
// p = (*p2 == ':') ? p2 + 1 : NULL;
