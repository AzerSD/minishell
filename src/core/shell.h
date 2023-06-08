/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 01:55:30 by asioud            #+#    #+#             */
/*   Updated: 2023/06/08 12:45:11 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
#define SHELL_H

# define PS1 "$ "
# define PS2 "> "

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

#include "../parsing/lexer.h"
#include "../parsing/parser.h"
#include "../builtins/builtins.h"
#include "../execution/executor.h"
#include "../symbol_table/symtab.h"
#include "../../libs/libft/includes/libft.h"

void prompt_display_ps1(void);
void prompt_display_ps2(void);
int parse_and_execute(t_cli *cli);

#endif
