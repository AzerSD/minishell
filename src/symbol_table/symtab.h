/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 07:05:51 by asioud            #+#    #+#             */
/*   Updated: 2023/07/03 20:23:13 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYMTAB_H
# define SYMTAB_H

/**
 * @brief defines the type of a symbol table entry's value
 * @param SYM_STR   Represent shell variables
 * @param SYM_FUNC  Represent functions
*/
enum						e_symbol_type
{
	SYM_STR,
	SYM_FUNC,
};

/**
 * @brief The symbol table entry structure
 * @param func_body	For shell functions. The AST of the function body
 * @param val_type  SYM_STR or SYM_FUNC

* @param flags		Different properties assigned to variables and functions like 
					export and readonly flags
 * @param name		The name of the shell variable represented by the entry
 * @param next		Pointer to the next symbol table entry
 * @param val		String value (for shell variables only)
*/
struct						s_symtab_entry
{
	struct s_node			*func_body;
	enum e_symbol_type		val_type;
	struct s_symtab_entry	*next;
	unsigned int			flags;
	char					*name;
	char					*val;
};

/**
 * @brief The symbol table structure
 * @param level 0 for Global, 1 and above for local
 * @param first First entry in the table's linked list
 * @param last  Last entry in the table's linkes list
*/
struct						s_symtab
{
	int						level;
	struct s_symtab_entry	*first;
	struct s_symtab_entry	*last;
};

/* maximum allowed symbol tables in the stack */
# define MAX_SYMTAB 256

/**
 * @brief the symbol table stack structure

 * @param symtab_count The number of the global symbol table currently
						 in the stack.
 * @param symtab_list   An array of pointers to the stack's symbol table
 * @param global_symtab Pointers to the global symbol tables.
 * @param local_symtab Pointers to the local symbol tables.
*/
struct						s_symtab_stack
{
	int						symtab_count;
	struct s_symtab			*symtab_list[MAX_SYMTAB];
	struct s_symtab			*global_symtab;
	struct s_symtab			*local_symtab;
};

void					update_entry(struct s_symtab_entry *entry, \
						char *new_val, char *name);

/**
 * @brief Opposite of symbtab_entry_s
 * it removes the symbol table entry whose key matches the given name

	* and frees the memory used by the entry and adjusts the linked list pointers to
 * remove the entry from the symbol table
*/
int						rem_from_symtab(struct s_symtab_entry *entry, \
						struct s_symtab *symtab);

/**
 * @brief This function searches the given symbol table,
	starting with the first entry.
 * If the entry’s key matches the variable name we’re looking for,
 * the function returns the entry. Otherwise, the function follows the linked
 * list pointers to look at each entry, in turn, until we find an entry whose
 * key matches our desired name. If no match is found, we return NULL.
*/
struct s_symtab_entry	*do_lookup(const char *str, \
						struct s_symtab *symtable);

/**
 * @brief This function adds a new entry to the local symbol table.
 * To ensure that each entry has a unique key, we first check to see
 * if an entry exists with the given name, by calling do_lookup()
 * If an entry with the given name exists, we simply
 * @return the existing entry, without adding a new one. Otherwise, we add the
 * entry, set its name, and adjust the symbol table's pointers. Lastly,
 * we return the newly added entry.
*/
struct s_symtab_entry	*add_to_symtab(const char *symbol);

/**
 * @brief searches for a symbol table entry whose key matches the given name.
 * The difference between this function and do_lookup() is this function searchs
 * the whole stack starting with the local symbol table.
 * This function is usefull for shell functions and script files.
*/
struct s_symtab_entry	*get_symtab_entry(const char *str);

/**
 * @brief creates a new, empty symbol table and pushes it on top of the stack.
 * @returns the newly created symbol table.
*/
struct s_symtab			*symtab_stack_push(void);

/**
 * @brief get_global_symtab
 * @returns pointers to the global symbol tables.
*/
struct s_symtab			*get_global_symtab(void);

/**
 * @brief get the local symbol tables
 * @return pointers to the local symbol tables.
*/
struct s_symtab			*get_local_symtab(void);

/**
 * @brief removes (or pops) the symbol table on top of the stack,
 * adjusting the stack pointers as needed.
 * @return the symbol table that was removed from the stack.
*/
struct s_symtab			*symtab_stack_pop(void);

/**
 * @brief create a new symbol table
*/
struct s_symtab			*new_symtab(void);

/**
 * @brief This function frees the memory used to store the old entry’s value
 * (if one exists). It then creates a copy of the new value and stores
 * it in the symbol table entry.
*/
void					symtab_entry_setval(struct s_symtab_entry *entry, \
						char *val);

/**
 * @brief Free the symbol table
 * Called when we're done working with a symbol table, and
 * we want to free the memory used by the symbol table and its entries.
*/
void					free_symtab(struct s_symtab *symtab);

void					export_symtab(void);

/**
 * @brief Initializes the symbol table stack.
 * Allocates memory and initializes the global symbol table.
*/
void					init_symtab_stack(void);

/**
 * @brief Initializes the symbol table stack, populates it with
 * environment variables from the global `environ` variable, and sets the
 * default prompt strings of our g_shell.
 * @see man environ
 * @see printenv
 */
void					init_symtab(char **env);

void					string_to_symtab(const char *env_var);

char					*get_varname(const char *str);

int						remove_entry_from_symtab(struct s_symtab_entry *entry, \
		struct s_symtab *symtab);

void					free_symtab_entry(struct s_symtab_entry *entry);

struct s_symtab_entry	*create_symtab_entry(const char *symbol);

void					add_entry_to_symtab(struct s_symtab *st, \
	struct s_symtab_entry *entry);

int						remove_subsequent_entry(struct s_symtab_entry *entry, \
		struct s_symtab *symtab);
#endif
