/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:33:58 by asioud            #+#    #+#             */
/*   Updated: 2023/06/08 18:10:18 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

#include "../core/shell.h"
#include "../symbol_table/symtab.h"


int export_builtin(int argc, ...)
{
    va_list		args;
	char		**argv;
	char		*env_var;

	env_var = NULL;
	va_start(args, argc);
	argv = va_arg(args, char **);
    if (argc == 1)
    {
        /* Display all environment variables (e.g., `declare -x var=value`) */
        while (*argv != NULL)
        {
            printf("declare -x %s\n", *argv);
            argv++;
        }
        va_end(args);
    }
    else
    {
		// export ls -> ls=''
		// export a=asdf -> a=asdf
        int i = 1;
        while ( i < argc)
        {
            /* Check if the argument is a valid environment variable */
			env_var = va_arg(args, char *);
            env_var = (argv[i]);
            if (env_var != NULL)
                printf("declare -x %s=%s\n", argv[i], env_var);
            i++;
        }
        va_end(args);
    }
	return(0);
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
