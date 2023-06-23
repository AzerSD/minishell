/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 05:03:22 by asioud            #+#    #+#             */
/*   Updated: 2023/06/23 18:05:29 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int file_exists(char *path)
{
	struct stat st;
	if (stat(path, &st) == 0 && S_ISREG(st.st_mode))
		return (1);
	else
	{
		errno = ENOENT;
		return 0;
	}
}

static char *build_path(char *start, char *end, char *file, int plen)
{
	char *path = my_malloc(&shell.memory, plen + 1 + strlen(file) + 1);
	if (!path)
		return (NULL);
	
	strncpy(path, start, plen);
	path[plen] = '\0';
	if (end[-1] != '/')
		strcat(path, "/");
	strcat(path, file);

	return path;
}

char *search_path(char *file)
{
	char *PATH = getenv("PATH");
	char *p = PATH;

	while (p && *p)
	{
		char *p2 = strchr(p, ':');
		if (!p2)
			p2 = p + strlen(p);
		int plen = p2 - p;
		if (plen == 0)
			plen = 1;

		char *path = build_path(p, p2, file, plen);
		if (!path)
			return (NULL);

		if (file_exists(path))
			return path;
		else
			free(path);

		p = (*p2 == ':') ? p2 + 1 : NULL;
	}

	errno = ENOENT;
	return (NULL);
}
