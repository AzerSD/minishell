/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 01:58:07 by asioud            #+#    #+#             */
/*   Updated: 2023/06/16 22:46:01 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

/**
 * @brief allocates and initializes a new node with the specified type.
 * It sets the type field and zeroes out the rest of the struct. 
 * @param type Type of node to create.
 * @return t_node* Our initialized node.
 */
t_node *new_node(enum e_node_type type)
{
	t_node *node = malloc(sizeof(t_node));

	if (!node)
		return NULL;
	memset(node, 0, sizeof(t_node));
	node->type = type;
	return node;
}

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
void add_child_node(t_node *parent, t_node *child)
{
	if (!parent || !child)
		return;
	if (!parent->first_child)
		parent->first_child = child;
	else
	{
		t_node *sibling = parent->first_child;
	
		while (sibling->next_sibling)
			sibling = sibling->next_sibling;
		sibling->next_sibling = child;
		child->prev_sibling = sibling;
	}
	parent->children++;
}

void add_parent_node(t_node* child, t_node* parent) {
	if (child == NULL || parent == NULL) {
		return;
	}

	add_child_node(parent, child);
}

/**
 * @brief This function sets the val_type of the node to VAL_STR and 
 * allocates memory for the string value to be stored in the node.
 * If successful, it copies the input string into the newly allocated 
 * memory and sets the val.str field of the node.
 * @param node 
 * @param val 
 */
void set_node_val_str(t_node *node, char *val)
{
	char *val2;

	node->val_type = VAL_STR;
	if (!val)
		node->val.str = NULL;
	else
	{
		val2 = malloc(strlen(val)+1);	
		if (!val2)
			node->val.str = NULL;
		else
		{
			strcpy(val2, val);
			node->val.str = val2;
		}
	}
}

/**
 * @brief Recursively frees the memory allocated for a node and its children.
 * It traverses the tree in depth-first order, freeing the memory for each
 * child and its siblings before finally freeing the parent node. 
 * @param node Our node structure to free.
 */
void free_node_tree(t_node *node)
{
	if (!node)
		return;
	t_node *child = node->first_child;
	
	while (child)
	{
		t_node *next = child->next_sibling;
		free_node_tree(child);
		child = next;
	}
	
	if (node->val_type == VAL_STR)
		if (node->val.str)
			free(node->val.str);
	free(node);
}

