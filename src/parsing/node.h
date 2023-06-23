/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 01:58:12 by asioud            #+#    #+#             */
/*   Updated: 2023/06/23 04:20:11 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef NODE_H
# define NODE_H


/**
 * Define the type of our AST Node
 * @param NODE_COMMAND represents the root node of a simple command
 * @param NODE_VAR	represents the simple command's child nodes
 * @param NODE_ASSIGNMENT represents the root node of an assignment
 * @param NODE_PIPE represents the root node of a pipe
 * @param 
*/
enum e_node_type
{
	NODE_COMMAND,           /* simple command */
	NODE_VAR,               /* variable name (or simply, a word)*/
	NODE_ASSIGNMENT,        /* assignment */
	NODE_PIPE,              /* pipe */
	NODE_LIST,			  /* list */
	NODE_INPUT,
	NODE_OUTPUT,
	NODE_APPEND,
	NODE_HEREDOC,
	NODE_FILE,
};

/**
 * Represents the types of values we can store in a given node structure
 * for simple commands we use only VAL_STR
*/
enum e_val_type
{
	VAL_SINT = 1,       /* signed int */
	VAL_UINT,           /* unsigned int */
	VAL_SLLONG,         /* signed long long */
	VAL_ULLONG,         /* unsigned long long */
	VAL_FLOAT,          /* floating point */
	VAL_LDOUBLE,        /* long double */
	VAL_CHR,            /* char */
	VAL_STR,            /* str (char pointer) */
};

/**
 * Represents the value we can store in a given node structure,
 * Each node can have only one typoe of value.
*/
union u_symval
{
	unsigned long long ullong;
	unsigned long      uint;
	long long          sllong;
	long double        ldouble;
	double             sfloat;
	long               sint;
	char               chr;
	char              *str;
};

/**
 * Represents an AST struct. it contains fields that tell us about
 * the node's type, the type of the node's value and the value itself
 * and pointers to children nodes and sibling nodes.
 * @param type the type of the node
 * @param val_type the type of the node's value
 * @param val the value of the node
 * @param children the number of children nodes
 * @param first_child the first child node
 * @param next_sibling the next sibling node
 * @param prev_sibling the previous sibling node
 * @param line_nbr the line number where the node's token was encountered
*/
typedef struct s_node
{
	enum e_node_type	type;
	enum e_val_type		val_type;
	union u_symval		val;
	struct s_node		*first_child;
	struct s_node		*next_sibling;
	struct s_node		*prev_sibling;
	int					children;
	int    				line_nbr;

} t_node ;

t_node	*new_node(enum e_node_type type);
void    add_child_node(t_node *parent, t_node *child);
void	add_parent_node(t_node *child, t_node *parent);
void    free_node_tree(t_node *node);
void    set_node_val_str(t_node *node, char *val);
void	print_ast(t_node *node, int indent);
#endif


// If we want to retrieve a node’s value, we need to check the val_type field and, according to what we find there, access the appropriate member of the val field. For simple commands, all nodes will have the following attributes:

//     type => NODE_COMMAND (root node) or NODE_VAR (command name and arguments list)
//     val_type => VAL_STR
//     val.str => pointer to the string value