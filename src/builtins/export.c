/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:33:58 by asioud            #+#    #+#             */
/*   Updated: 2023/06/19 20:33:40 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static char* get_varname(const char *str)
{
    char* equalsSignPosition = strchr(str, '=');
    if (equalsSignPosition)
	{
        int len = equalsSignPosition - str;
        char *varName = malloc(len + 1);
        strncpy(varName, str, len);
        varName[len] = '\0';
        return varName;
    }
	else
        return NULL;
}

int	ft_export(int argc, ...)
{
	char	*ep;
	va_list	args;
	char	**argv;
	int		i;
	char *var_name;

	va_start(args, argc);
	argv = va_arg(args, char **);
	if (argc == 1)
	{
		dump_export_local_symtab();
		va_end(args);
	}
	else
	{
		if(argv[1] != NULL && (argv[2] == NULL || ft_strcmp(argv[2], "") == 0))
		{
			if (is_valid_variable_name(argv[2]))
				string_to_symtab((const char *)argv[1]);
		}
		i = 1;
		while (i < argc)
		{
			var_name = get_varname(argv[i]);
			if (is_valid_variable_name(var_name))
				string_to_symtab((const char *)argv[i]);
			i++;
		}
		va_end(args);
	}
	return (0);
}
