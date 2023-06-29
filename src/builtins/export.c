/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:33:58 by asioud            #+#    #+#             */
/*   Updated: 2023/06/28 10:18:31 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_export(int argc, ...)
{
    struct s_symtab_entry   *entry = NULL;
    struct s_symtab         *symtab = s_symtab_stack.local_symtab;
    char   **argv;
    char   *name;
    char   *value;
    char   *old_value;

    va_list args;
    va_start(args, argc);
    argv = va_arg(args, char **);
    entry = symtab->first;
    va_end(args);
    
    if (argc == 1)
    {
        while (entry)
        {
            ft_printf_fd(STDERR_FILENO, "declare -x %s=%s\n", entry->name, entry->val);
            entry = entry->next;
        }
        return (0);   
    }
    else
    {
        va_start(args, argc);
        argv = va_arg(args, char **);
        va_end(args);

        // Check if the argument starts with a hyphen
        if (argv[1][0] == '-')
        {
            ft_printf_fd(STDERR_FILENO, "bash: export: --: invalid option\nexport: usage: export [-nf] [name[=value] ...] or export -p\n");
            return 2;
        }

        name = get_varname(argv[1]);
        if (!name)
            name = argv[1];
        if (strstr(argv[1], "+=") != NULL)
        {
            name = strtok(argv[1], "+=");
            if (!name || !is_valid_variable_name(argv[1]))
            {
                ft_printf_fd(STDERR_FILENO, "minishell: export: `%s': not a valid identifier\n", argv[1]);
                return 1;
            }
            value = strtok(NULL, "+=");

            entry = do_lookup(name, symtab);
            if (entry)
                old_value = entry->val;
            else
                old_value = "";

            // Append the value to the old value
            char *new_value = malloc(strlen(old_value) + strlen(value) + 1);
            strcpy(new_value, old_value);
            strcat(new_value, value);

            // Set the new value
            setenv(name, new_value, 1);
            free(new_value);

            return 0;
        }
        else if (strchr(argv[1], '=') != NULL)
        {
            if (is_valid_variable_name(name))
            {
                string_to_symtab(argv[1]);
                return 0;
            }
            else
            {
                ft_printf_fd(STDERR_FILENO, "minishell: export: `%s': not a valid identifier\n", name);
                return 1;
            }
        }
        else
        {
            entry = do_lookup(argv[1], symtab);
            if (entry)
            {
                ft_printf_fd(STDERR_FILENO, "declare -x %s=%s\n", entry->name, entry->val);
                return 0;
            }
            else if (!is_valid_variable_name(name))
            {
                ft_printf_fd(STDERR_FILENO, "minishell: export: `%s': not a valid identifier\n", argv[1]);
                return 1;
            }
            return 0;
        }
    }
    return 0;
}