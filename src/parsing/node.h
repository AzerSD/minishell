/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 01:58:12 by asioud            #+#    #+#             */
/*   Updated: 2023/07/03 04:49:11 by asioud           ###   ########.fr       */
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
enum					e_node_type
{
	NODE_COMMAND,
	NODE_VAR,
	NODE_ASSIGNMENT,
	NODE_PIPE,
	NODE_LIST,
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
enum					e_val_type
{
	VAL_SINT = 1,
	VAL_UINT,
	VAL_SLLONG,
	VAL_ULLONG,
	VAL_FLOAT,
	VAL_LDOUBLE,
	VAL_CHR,
	VAL_STR,
};

/**
 * Represents the value we can store in a given node structure,
 * Each node can have only one typoe of value.
*/
union					u_symval
{
	unsigned long long	ullong;
	unsigned long		uint;
	long long			sllong;
	long double			ldouble;
	double				sfloat;
	long				sint;
	char				chr;
	char				*str;
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
	int					line_nbr;

}						t_node;

/**
 * @brief allocates and initializes a new node with the specified type.
 * It sets the type field and zeroes out the rest of the struct. 
 * @param type Type of node to create.
 * @return t_node* Our initialized node.
 */
t_node					*new_node(enum e_node_type type);

/**
 * @brief Adds a new child node to the specified parent node. 
 * If the parent node doesn't have any children, it sets the first_child
 * pointer to the new child node.
 * If the parent node already has children, it traverses the siblings using
 * the next_sibling pointer and appends the new child node at the end of the
 * sibling list.
 * The prev_sibling pointer of the new child node is set accordingly,
 * and the children counter of the parent node is incremented.
 * @param parent 
 * @param child 
 */
void					add_child_node(t_node *parent, t_node *child);
void					add_parent_node(t_node *child, t_node *parent);

/**
 * @brief Recursively frees the memory allocated for a node and its children.
 * It traverses the tree in depth-first order, freeing the memory for each
 * child and its siblings before finally freeing the parent node. 
 * @param node Our node structure to free.
 */
void					free_node_tree(t_node *node);

/**
 * @brief This function sets the val_type of the node to VAL_STR and 
 * allocates memory for the string value to be stored in the node.
 * If successful, it copies the input string into the newly allocated 
 * memory and sets the val.str field of the node.
 * @param node 
 * @param val 
 */
void					set_node_val_str(t_node *node, char *val);
void					print_ast(t_node *node, int indent);

#endif
