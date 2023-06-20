/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 07:28:23 by asioud            #+#    #+#             */
/*   Updated: 2023/06/20 00:40:22 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void dump_local_symtab(void)
{
	struct s_symtab *symtab = s_symtab_stack.local_symtab;
	int i = 0;
	int indent = symtab->level * 4;
	fprintf(stderr, "%*sSymbol table [Level %d]:\r\n", indent, " ", symtab->level);
	fprintf(stderr, "%*s===========================\r\n", indent, " ");
	fprintf(stderr, "%*s  No               Symbol                    Val\r\n", indent, " ");
	fprintf(stderr, "%*s------ -------------------------------- ------------\r\n", indent, " ");
	struct s_symtab_entry *entry = symtab->first;
	while (entry)
	{
		if (entry->val)
			fprintf(stderr, "%*s[%04d] %-32s '%s'\r\n", indent, " ",
					i++, entry->name, entry->val);
		else
			fprintf(stderr, "%*s[%04d] %-32s \r\n", indent, " ",
					i++, entry->name);
		entry = entry->next;
	}
	fprintf(stderr, "%*s------ -------------------------------- ------------\r\n", indent, " ");
}

void dump_export_local_symtab(void)
{
	struct s_symtab *symtab = s_symtab_stack.local_symtab;

	struct s_symtab_entry *entry = symtab->first;
	while (entry)
	{
		if (is_valid_variable_name(entry->name))
		{
			if (entry->val)
				fprintf(stderr, "declare -x %s=%s\n", entry->name, entry->val);
			else
				fprintf(stderr, "declare -x %s\n", entry->name);
		}
		entry = entry->next;
	}
}
struct s_symtab_entry *add_to_symtab(const char *symbol)
{
	if (!symbol || symbol[0] == '\0')
		return NULL;
	struct s_symtab *st = s_symtab_stack.local_symtab;
	struct s_symtab_entry *entry = NULL;

	if ((entry = do_lookup(symbol, st)))
		return entry;

	entry = malloc(sizeof(struct s_symtab_entry));
	if (!entry)
	{
		fprintf(stderr, "fatal error: no memory for new symbol table entry\n");
		exit(EXIT_FAILURE);
	}
	memset(entry, 0, sizeof(struct s_symtab_entry));
	entry->name = malloc(strlen(symbol)+1);
	if (!entry->name)
	{
		fprintf(stderr, "fatal error: no memory for new symbol table entry\n");
		exit(EXIT_FAILURE);
	}
	strcpy(entry->name, symbol);
	if (!st->first)
	{
		st->first      = entry;
		st->last       = entry;
	}
	else
	{
		st->last->next = entry;
		st->last       = entry;
	}
	return entry;
}

int rem_from_symtab(struct s_symtab_entry *entry, struct s_symtab *symtab)
{
	int res = 0;
	if (entry->val)
		free(entry->val);
	if (entry->func_body)
		free_node_tree(entry->func_body);
	free(entry->name);
	if (symtab->first == entry)
	{
		symtab->first = symtab->first->next;
		if (symtab->last == entry)
			symtab->last = NULL;
		res = 1;
	}
	else
	{
		struct s_symtab_entry *e = symtab->first;
		struct s_symtab_entry *p = NULL;
		while (e && e != entry)
		{
			p = e;
			e = e->next;
		}
		if (e == entry)
		{
			p->next = entry->next;
			res = 1;
		}
	}
	free(entry);
	return res;
}

struct s_symtab_entry *do_lookup(const char *str, struct s_symtab *symtable)
{
	if (!str || !symtable)
		return NULL;
	struct s_symtab_entry *entry = symtable->first;
	while (entry)
	{
		if (strcmp(entry->name, str) == 0)
			return entry;
		entry = entry->next;
	}
	return NULL;
}

struct s_symtab_entry *get_symtab_entry(const char *str)
{
	int i = s_symtab_stack.symtab_count-1;
	do
	{
		struct s_symtab *symtab = s_symtab_stack.symtab_list[i];
		struct s_symtab_entry *entry = do_lookup(str, symtab);
		if (entry)
		{
			return entry;
		}
	} while (--i >= 0);
	return NULL;
}

void symtab_entry_setval(struct s_symtab_entry *entry, char *val)
{
	if (entry->val)
	{
		free(entry->val);
	}
	if (!val)
	{
		entry->val = NULL;
	}
	else
	{
		char *val2 = malloc(strlen(val)+1);        if (val2)
		{
			strcpy(val2, val);
		}
		else
		{
			fprintf(stderr, "error: no memory for symbol table entry's value\n");
		}        entry->val = val2;
	}
}

void update_entry(struct s_symtab_entry *entry, char *new_val, char *name)
{
	struct s_symtab			*st;

	st = s_symtab_stack.local_symtab;

	entry = do_lookup(name, st);
	if (!entry)
	{
		fprintf(stderr, "%s not set", name);
	}
	symtab_entry_setval(entry, new_val);

}
