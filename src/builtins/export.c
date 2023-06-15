/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:33:58 by asioud            #+#    #+#             */
/*   Updated: 2023/06/16 01:40:36 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
#include "../core/shell.h"
#include "../symbol_table/symtab.h"

// struct s_symtab_entry
// {
// 	struct s_node           *func_body;
// 	enum e_symbol_type      val_type;
// 	struct s_symtab_entry   *next;
// 	unsigned int            flags;
// 	char                    *name;
// 	char                    *val;
// };

int	ft_export(int argc, ...)
{
	va_list	args;
	char	**argv;
	char	*envar;
	int		i;

	envar = NULL;
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
			envar = va_arg(args, char *);
			string_to_symtab((const char *)argv[1]);
		}
		i = 1;
		while (i < argc)
		{
			/* Check if the argument is a valid environment variable */
			envar = va_arg(args, char *);
			string_to_symtab((const char *)argv[i]);
			i++;
		}
		va_end(args);
	}
	return (0);
}
