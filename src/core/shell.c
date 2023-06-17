/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 01:45:52 by asioud            #+#    #+#             */
/*   Updated: 2023/06/17 22:58:10 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	main(int argc, char **argv)
{
	t_cli			cli;
	char			*cmd;
	struct termios	mirror_termios;

	(void)argc;
	(void)argv;
	init_symtab();
	signals(&mirror_termios);
	while (true)
	{
		cmd = readline("minishell> ");
		rl_clear_history();
		if (!cmd)
			exit(EXIT_SUCCESS);
		if (cmd[0] == '\0' || strncmp(cmd, "\n", 1) == 0)
		{
			free(cmd);
			continue ;
		}
		if (strncmp(cmd, "exit", 5) == 0)
		{
			free(cmd);
			ft_exit(1, 0);
		}
		/* If it is a terminal not running by a script or smth*/
		if (isatty(STDIN_FILENO))
			add_history(cmd);
		/* Init Command Line Struct */
		cli.buffer = cmd;
		cli.buff_size = strlen(cmd);
		cli.cur_pos = INIT_SRC_POS;
		parse_and_execute(&cli);
		free(cmd);;
	}
	clear_history();
	exit(EXIT_SUCCESS);
}

// void print_ast(t_node *node, int indent) {
//     if (node == NULL) {
//         return;
//     }

//     for (int i = 0; i < indent - 1; i++) {
//         printf("  │");
//     }

//     if (indent > 0) {
//         printf("  ├─");
//     }

//     printf("Value: %s,	level: %u\n", \
// 			 node->val.str, node->type);

//     // Recursively print child nodes
//     t_node *child = node->first_child;
//     while (child != NULL) {
//         print_ast(child, indent + 1);
//         child = child->next_sibling;
//     }
// }


int parse_and_execute(t_cli *cli)
{
	t_node		*ast_cmd;
	t_token		*tok;
	t_curr_tok	*curr;
	curr = malloc(sizeof(t_curr_tok));
	skip_whitespaces(cli);
	tok = get_token(cli, curr);
	ast_cmd = parse_cmd(tok, curr);
	// print_ast(ast_cmd, 0);
	if (!ast_cmd)
		return 1;
	execc(ast_cmd);

	// free_node_tree(ast_cmd);
	return (0);
}
