/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 01:45:52 by asioud            #+#    #+#             */
/*   Updated: 2023/06/11 18:44:32 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./shell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "../signals/signals.h"


int main(int argc, char **argv)
{
	t_cli		cli;
	char		*cmd;

	(void) argc;
	(void) argv;
	init_symtab();
	
	while (true)
	{
		cmd = readline("minishell> ");
		rl_clear_history();
		if (!cmd)
			exit(EXIT_SUCCESS);
		if (cmd[0] == '\0' || strncmp(cmd, "\n", 1) == 0)
		{
			free(cmd);
			continue;
		}
		if (strncmp(cmd, "exit", 5) == 0)
		{
			free(cmd);
			exit_builtin(1, 0);
		}
		
		/* If it is a terminal not running by a script or smth*/
		if (isatty(STDIN_FILENO))
			add_history(cmd);
		
		/* Init Command Line Struct */
		cli.buffer   = cmd;
		cli.buff_size  = strlen(cmd);
		cli.cur_pos   = INIT_SRC_POS;
		
		parse_and_execute(&cli);
		free(cmd);
	}
	clear_history();
	exit(EXIT_SUCCESS);
}

void print_ast(t_node *node, int indent) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < indent - 1; i++) {
        printf("  │");
    }

    if (indent > 0) {
        printf("  ├─");
    }

    printf("Value: %s,	level: %u\n", \
			 node->val.str, node->type);

    // Recursively print child nodes
    t_node *child = node->first_child;
    while (child != NULL) {
        print_ast(child, indent + 1);
        child = child->next_sibling;
    }
}

int parse_and_execute(t_cli *cli)
{
	t_node		*ast_cmd;
	t_token		*tok;
	t_curr_tok	*curr = malloc(sizeof(t_curr_tok));

	skip_whitespaces(cli);
	tok = get_token(cli, curr);
	ast_cmd = parse_cmd(tok, curr);
	print_ast(ast_cmd, 0);
	if (!ast_cmd)
		return 1;
	execc(ast_cmd);
	// free_node_tree(ast_cmd);
	return (0);
}



// int parse_and_execute(t_cli* cli) {
// 	t_node* ast = new_node(NODE_COMMAND);
// 	t_node* c1 = new_node(NODE_COMMAND);
// 	t_node* c2 = new_node(NODE_COMMAND);
// 	t_node* c3 = new_node(NODE_COMMAND);
// 	t_node* c4 = new_node(NODE_COMMAND);

// 	ast->val.str = "ast";
// 	c1->val.str = "c1";
// 	c2->val.str = "c2";
// 	c3->val.str = "c3";
// 	c4->val.str = "c4";

// 	add_parent_node(c1, ast);
// 	add_parent_node(c2, ast);
// 	add_parent_node(c3, c2);
// 	add_parent_node(c4, c3);

// 	print_ast(ast, 0);

// 	// Clean up the tree nodes
// 	// ...

// 	(void)cli;
// 	return 0;
// }