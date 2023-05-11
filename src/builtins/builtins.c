/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 05:41:31 by asioud            #+#    #+#             */
/*   Updated: 2023/05/11 12:33:30 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/**
 * A builtin utility (a.k.a. builtin or internal command) is a command whose
 * code is compiled as part of the shell executable itself, i.e. the shell
 * doesn’t need to execute an external program, nor does it need to fork a 
 * new process in order to execute the command. Many of the commands we use 
 * on daily basis, such as cd, echo, export, and readonly are in fact builtin 
 * utilities. You can read more about shell builtin utilities in this POSIX 
 * standard. 
 *https://www.gnu.org/software/bash/manual/html_node/Shell-Builtin-Commands.html
 */
#include "../core/shell.h"

struct s_builtin builtins[] =
{   
    { "dump"    , dump },
    { "echo"    , echo },
    { "env"     , env },
    { "pwd"    , pwd },
    { "cd"      , cd }, /* lacking changing pwd and old_pwd*/
    { "export"  , export },
    { "unset"   , unset },
    { "exit"    , exit_builtin },
    
};

int builtins_count = sizeof(builtins)/sizeof(struct s_builtin);
