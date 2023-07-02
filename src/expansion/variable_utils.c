/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 23:27:27 by asioud            #+#    #+#             */
/*   Updated: 2023/07/02 23:47:48 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_svar_expand(struct s_var_expand *v)
{
	v->entry = NULL;
	v->len = 0;
	v->get_length = 0;
	v->sub = NULL;
	v->var_name = NULL;
	v->empty_val = NULL;
	v->tmp = NULL;
	v->setme = 0;
	v->p = NULL;
	v->longest = 0;
	v->p2 = NULL;
	v->expanded = 0;
	memset(v->buf, 0, sizeof(v->buf));
}

void	check_result(struct s_var_expand *var)
{
	if (var->tmp)
	{
		if ((var->tmp = word_expand_to_str(var->tmp)))
			var->expanded = 1;
	}
	if (var->setme)
	{
		if (!var->entry)
			var->entry = add_to_symtab(var->var_name);
		if (var->entry)
			symtab_entry_setval(var->entry, var->tmp);
	}
	if (var->get_length)
	{
		if (!var->tmp)
			sprintf(var->buf, "0");
		else
			sprintf(var->buf, "%lu", strlen(var->tmp));
		var->p = my_malloc(&shell.memory, strlen(var->buf) + 1);
		if (var->p)
			strcpy(var->p, var->buf);
	}
	else
	{
		var->p = my_malloc(&shell.memory, strlen(var->tmp) + 1);
		if (var->p)
			strcpy(var->p, var->tmp);
	}
}

char	*setup_var(char *orig_var_name, struct s_var_expand *var)
{
	if (!orig_var_name)
		return (NULL);
	orig_var_name++;
	var->len = strlen(orig_var_name);
	if (*orig_var_name == '{')
	{
		orig_var_name[var->len - 1] = '\0';
		orig_var_name++;
	}
	if (!*orig_var_name)
		return (NULL);
	var->get_length = 0;
	if (*orig_var_name == '#')
	{
		if (strchr(orig_var_name, ':'))
		{
			fprintf(stderr, "error: invalid variable substitution: %s\n",
					orig_var_name);
			return (INVALID_VAR);
		}
		var->get_length = 1;
		orig_var_name++;
	}
	return (orig_var_name);
}

char	*exit_code_to_str(unsigned char status)
{
	static char	str[4];

	snprintf(str, sizeof(str), "%d", status);
	return (str);
}

char	*exit_code_expansion(char *orig_var_name)
{
	char	*exit_code_str;
	char	*exit_code_copy;

	exit_code_str = exit_code_to_str(shell.status);
	exit_code_copy = strdup(exit_code_str);
	if (exit_code_copy == NULL)
	{
		fprintf(stderr,
				"error: failed to allocate memory for exit code\n");
		return (INVALID_VAR);
	}
	return (exit_code_copy);
}
