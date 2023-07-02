/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 11:14:10 by ygolshan          #+#    #+#             */
/*   Updated: 2023/07/02 13:00:05 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// struct s_symtab_entry	*add_to_symtab(const char *symbol)
// {
// 	struct s_symtab			*st;
// 	struct s_symtab_entry	*entry;

// 	if (!symbol || symbol[0] == '\0')
// 		return (NULL);
// 	st = s_symtab_stack.local_symtab;
// 	entry = NULL;
// 	if (entry == do_lookup(symbol, st))
// 		return (entry);
// 	entry = my_malloc(&shell.memory, sizeof(struct s_symtab_entry));
// 	if (!entry)
// 	{
// 		fprintf(stderr, "fatal error: no memory for new symbol table entry\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	memset(entry, 0, sizeof(struct s_symtab_entry));
// 	entry->name = my_malloc(&shell.memory, strlen(symbol) + 1);
// 	if (!entry->name)
// 	{
// 		fprintf(stderr, "fatal error: no memory for new symbol table entry\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	strcpy(entry->name, symbol);
// 	if (!st->first)
// 	{
// 		st->first = entry;
// 		st->last = entry;
// 	}
// 	else
// 	{
// 		st->last->next = entry;
// 		st->last = entry;
// 	}
// 	return (entry);
// }

void	fatal_error(const char *message)
{
	fprintf(stderr, "fatal error: %s\n", message);
	exit(EXIT_FAILURE);
}

struct s_symtab_entry	*add_to_symtab(const char *symbol)
{
	struct s_symtab_entry	*entry;
	struct s_symtab			*st;

	if (!symbol || symbol[0] == '\0')
		return (NULL);
	entry = do_lookup(symbol, s_symtab_stack.local_symtab);
	if (entry)
		return (entry);
	entry = my_malloc(&shell.memory, sizeof(struct s_symtab_entry));
	if (!entry)
		fatal_error("no memory for new symbol table entry");
	entry->name = my_malloc(&shell.memory, strlen(symbol) + 1);
	if (!entry->name)
		fatal_error("no memory for new symbol table entry");
	strcpy(entry->name, symbol);
	st = s_symtab_stack.local_symtab;
	if (!st->first)
		st->first = entry;
	else
		st->last->next = entry;
	return (st->last = entry);
}

struct s_symtab_entry	*do_lookup(const char *str, struct s_symtab *symtable)
{
	struct s_symtab_entry	*entry;

	if (!str || !symtable)
		return (NULL);
	entry = symtable->first;
	while (entry)
	{
		if (strcmp(entry->name, str) == 0)
			return (entry);
		entry = entry->next;
	}
	return (NULL);
}

struct s_symtab_entry	*get_symtab_entry(const char *str)
{
	int						i;
	struct s_symtab			*symtab;
	struct s_symtab_entry	*entry;

	i = s_symtab_stack.symtab_count - 1;
	entry = NULL;
	while (i >= 0 && !entry)
	{
		symtab = s_symtab_stack.symtab_list[i];
		entry = do_lookup(str, symtab);
		i--;
	}
	return (entry);
}

// void	symtab_entry_setval(struct s_symtab_entry *entry, char *val)
// {
// 	char	*val2;

// 	if (entry->val)
// 	{
// 		free(entry->val);
// 	}
// 	if (!val)
// 	{
// 		entry->val = NULL;
// 	}
// 	else
// 	{
// 		val2 = my_malloc(&shell.memory, strlen(val) + 1);
// 		if (val2)
// 			strcpy(val2, val);
// 		else
// 			fprintf(stderr,
// 				"error: no memory for symbol table entry's value\n");
// 		entry->val = val2;
// 	}
// }

void	update_entry(struct s_symtab_entry *entry, char *new_val, char *name)
{
	entry = do_lookup(name, s_symtab_stack.local_symtab);
	if (!entry)
	{
		entry = add_to_symtab(name);
	}
	symtab_entry_setval(entry, new_val);
}
