/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 05:03:22 by asioud            #+#    #+#             */
/*   Updated: 2023/07/03 20:22:51 by asioud           ###   ########.fr       */
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

	path = my_malloc(&g_shell.memory, plen + 1 + ft_strlen(file) + 1);
	if (!path)
		return (NULL);
	ft_strncpy(path, start, plen);
	path[plen] = '\0';
	if (end[-1] != '/')
		ft_strcat(path, "/");
	ft_strcat(path, file);
	return (path);
}

char	*build_path_and_check_existence(char *p, char *p2, char *file, int plen)
{
	char	*path;

	path = build_path(p, p2, file, plen);
	if (!path)
		return (NULL);
	if (file_exists(path))
		return (path);
	else
		free(path);
	return (NULL);
}

char	*search_path(char *file)
{
	char	*path;
	char	*p;
	char	*p2;
	int		plen;
	char	*valid_path;

	path = getenv("PATH");
	p = path;
	while (p && *p)
	{
		p2 = ft_strchr(p, ':');
		if (!p2)
			p2 = p + strlen(p);
		plen = p2 - p;
		if (plen == 0)
			plen = 1;
		valid_path = build_path_and_check_existence(p, p2, file, plen);
		if (valid_path != NULL)
			return (valid_path);
		if (*p2 == ':')
			p = p2 + 1;
		else
			p = NULL;
	}
	return ((errno = ENOENT), NULL);
}
