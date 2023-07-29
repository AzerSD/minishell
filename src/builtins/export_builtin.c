/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:33:58 by asioud            #+#    #+#             */
/*   Updated: 2023/06/07 15:56:28 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/lailah/MacDesk42/minishell/src/symbol_table/symtab.h"
// // if argc is equal to 1, it means that no specific environment variables were provided as arguments, 
// and you should display all environment variables.
// // In the first case, you can use the environ global variable (which is an array of 
// strings) to access all environment variables. Iterate through the array and print 
// each variable using the format "declare -x var=value".
// // If argc is greater than 1, it means specific environment variables were passed 
// as arguments, and you should display only those variables.
// // Iterate through the argv array starting from index 1 (index 0 is the program 
// name itself) and check if each argument corresponds to a valid environment variable 
// using getenv().
// // If getenv() returns a non-NULL value, it means the argument is a valid environment 
// variable. Print it using the format "declare -x var=value".


static void export_builtin(int argc, char **argv)
{
    if (argc == 1)
    {
        /* Display all environment variables (e.g., `declare -x var=value`) */
        char **env = environ
        /* Iterate through the environment variables */
        while (*env != NULL)
        {/* Print each environment variable */
            printf("declare -x %s\n", *env);
            env++;
        }
    }
    else
    {/* Display only the environment variables passed as arguments */
        int i = 1;
        /* Iterate through the arguments */
        while ( i < argc;)
        {
            /* Check if the argument is a valid environment variable */
            char *env_var = getenv(argv[i]);
            if (env_var != NULL)
            {/* Print the environment variable */
                printf("declare -x %s=%s\n", argv[i], env_var);
            }
            i++;
        }
    }
}

// The error message indicates that the `export_builtin` function declared in the `builtins.h` header file is not being used in your code, resulting in an "unused function" warning. This warning is treated as an error due to the `-Werror` flag passed to the compiler.

// To resolve this issue, you have a few options:

// 1. If you plan to use the `export_builtin` function later in your code, you can remove the `-Wunused-function` flag to disable the warning as an error. Modify the compilation flags to remove the `-Werror` option.

// 2. If you don't plan to use the `export_builtin` function at all, you can simply remove its declaration from the `builtins.h` header file. This will eliminate the warning and the error.

// 3. If you want to keep the `export_builtin` function but suppress the warning, you can use the `-Wunused-function` attribute to indicate that it is intentionally unused. You can modify the function declaration in `builtins.h` as follows:

//    ```c
//    static void export_builtin(int argc, char **argv) __attribute__((unused));
//    ```

//    This attribute tells the compiler to ignore the unused function warning for `export_builtin`.

// Choose the option that best suits your needs based on whether you intend to use the `export_builtin` function or not.