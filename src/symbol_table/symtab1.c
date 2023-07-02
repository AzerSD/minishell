/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 07:28:23 by asioud            #+#    #+#             */
/*   Updated: 2023/07/02 17:27:29 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	dump_local_symtab(void)
// {
// 	struct s_symtab			*symtab;
// 	int						i;
// 	int						indent;
// 	struct s_symtab_entry	*entry;

// 	symtab = s_symtab_stack.local_symtab;
// 	i = 0;
// 	indent = symtab->level * 4;
// 	fprintf(stderr, "%*sSymbol table [Level %d]:\r\n", indent, " ",
// 		symtab->level);
// 	fprintf(stderr, "%*s===========================\r\n", indent, " ");
// 	fprintf(stderr, "%*s  No               Symbol                    Val\r\n",
// 		indent, " ");
// 	fprintf(stderr,
// 		"%*s------ -------------------------------- ------------\r\n",
// 		indent, " ");
// 	entry = symtab->first;
// 	while (entry)
// 	{
// 		if (entry->val)
// 			fprintf(stderr, "%*s[%04d] %-32s '%s'\r\n", indent, " ", i++,
// 				entry->name, entry->val);
// 		else
// 			fprintf(stderr, "%*s[%04d] %-32s \r\n", indent, " ", i++,
// 				entry->name);
// 		entry = entry->next;
// 	}
// 	fprintf(stderr,
// 		"%*s------ -------------------------------- ------------\r\n",
// 		indent, " ");
// }

// void dump_local_symtab(void)
// {
// 	struct s_symtab			*symtab;
// 	int						indent;
// 	int						i;
// 	struct s_symtab_entry	*entry;

// 	i = 0;
// 	symtab = s_symtab_stack.local_symtab;
// 	indent = symtab->level * 4;
// 	entry = symtab->first;

// 	fprintf(stderr, "%*sSymbol table [Level %d]:\n"
// , indent,
// " ", symtab->level);
// 	fprintf(stderr, "%*s===========================\n", indent, " ");
// 	fprintf(stderr, "%*s  No               Symbol                    Val\n",
// 		indent, " ");
// 	fprintf(stderr, "%*s------ -------------------------------- ------------\n",
// 		indent, " ");
// 	while (entry)
// 	{
// 		fprintf(stderr, "%*s[%04d] %-32s ", indent, " ", i++, entry->name);
// 		if (entry->val)
// 			fprintf(stderr, "'%s'\n", entry->val);
// 		else
// 			fprintf(stderr, "\n");
// 		entry = entry->next;
// 	}
// 	fprintf(stderr, "%*s------ -------------------------------- ------------\n",
// 		indent, " ");
// }

void	print_symtab_header(const struct s_symtab *symtab, int indent)
{
	int							i;
	const struct s_symtab_entry	*entry;

	i = 0;
	fprintf(stderr, "%*sSymbol table [Level %d]:\n", indent, " ", symtab->level);
	fprintf(stderr, "%*s===========================\n", indent, " ");
	fprintf(stderr, "%*s  No               Symbol                    Val\n",
		indent, " ");
	fprintf(stderr, "%*s------ -------------------------------- ------------\n",
		indent, " ");
	entry = symtab->first;
	while (entry)
	{
		fprintf(stderr, "%*s[%04d] %-32s ", indent, " ", i++, entry->name);
		if (entry->val)
			fprintf(stderr, "'%s'\n", entry->val);
		else
			fprintf(stderr, "\n");
		entry = entry->next;
	}
}

// void print_symtab_entries(const struct s_symtab *symtab, int indent)
// {
// 	int i = 0;
// 	const struct s_symtab_entry *entry = symtab->first;

// 	while (entry)
// 	{
// 		fprintf(stderr, "%*s[%04d] %-32s ", indent, " ", i++, entry->name);
// 		if (entry->val)
// 			fprintf(stderr, "'%s'\n", entry->val);
// 		else
// 			fprintf(stderr, "\n");
// 		entry = entry->next;
// 	}
// }

void	dump_local_symtab(void)
{
	const struct s_symtab		*symtab;
	int							indent;

	symtab = s_symtab_stack.local_symtab;
	indent = symtab->level * 4;
	print_symtab_header(symtab, indent);
}

void	dump_export_local_symtab(void)
{
	struct s_symtab			*symtab;
	struct s_symtab_entry	*entry;

	symtab = s_symtab_stack.local_symtab;
	entry = symtab->first;
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

// int	rem_from_symtab(struct s_symtab_entry *entry, struct s_symtab *symtab)
// {
// 	int						res;
// 	struct s_symtab_entry	*e;
// 	struct s_symtab_entry	*p;

// 	res = 0;
// 	if (entry->val)
// 		free(entry->val);
// 	if (entry->func_body)
// 		free_node_tree(entry->func_body);
// 	free(entry->name);
// 	if (symtab->first == entry)
// 	{
// 		symtab->first = symtab->first->next;
// 		if (symtab->last == entry)
// 			symtab->last = NULL;
// 		res = 1;
// 	}
// 	else
// 	{
// 		e = symtab->first;
// 		p = NULL;
// 		while (e && e != entry)
// 		{
// 			p = e;
// 			e = e->next;
// 		}
// 		if (e == entry)
// 		{
// 			p->next = entry->next;
// 			res = 1;
// 		}
// 	}
// 	free (entry);
// 	return (res);
// }

int	rem_from_symtab(struct s_symtab_entry *entry, struct s_symtab *symtab)
{
	struct s_symtab_entry	*prev;

	if (symtab->first == entry)
	{
		symtab->first = symtab->first->next;
		if (symtab->last == entry)
			symtab->last = NULL;
		free_symtab_entry(entry);
		return (1);
	}
	prev = symtab->first;
	while (prev && prev->next != entry)
		prev = prev->next;
	if (prev)
	{
		prev->next = entry->next;
		free_symtab_entry(entry);
		return (1);
	}
	return (0);
}

void	free_symtab_entry(struct s_symtab_entry *entry)
{
	if (entry->val)
		free(entry->val);
	if (entry->func_body)
		free_node_tree(entry->func_body);
	free(entry->name);
	free(entry);
}

// struct s_symtab_entry	
// *do_lookup(const char *str, struct s_symtab *symtable)
// {
// 	struct s_symtab_entry	*entry;

// 	if (!str || !symtable)
// 		return (NULL);
// 	entry = symtable->first;
// 	while (entry)
// 	{
// 		if (strcmp(entry->name, str) == 0)
// 			return (entry);
// 		entry = entry->next;
// 	}
// 	return (NULL);
// }

// struct s_symtab_entry	*get_symtab_entry(const char *str)
// {
// 	int						i;
// 	struct s_symtab			*symtab;
// 	struct s_symtab_entry	*entry;

// 	i = s_symtab_stack.symtab_count - 1;
// 	entry = NULL;
// 	while (i >= 0 && !entry)
// 	{
// 		symtab = s_symtab_stack.symtab_list[i];
// 		entry = do_lookup(str, symtab);
// 		i--;
// 	}
// 	return (entry);
// }

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

// void	update_entry(struct s_symtab_entry *entry, char *new_val, char *name)
// {
// 	entry = do_lookup(name, s_symtab_stack.local_symtab);
// 	if (!entry)
// 	{
// 		entry = add_to_symtab(name);
// 	}
// 	symtab_entry_setval(entry, new_val);
// }

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
