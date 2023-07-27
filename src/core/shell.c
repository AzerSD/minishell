/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 01:45:52 by asioud            #+#    #+#             */
/*   Updated: 2023/07/27 22:19:17 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_cli			cli;
	char			*cmd;
	struct termios	mirror_termios;
	int				original_stdout;

	(void)argc;
	(void)argv;
	init_symtab(env);
	signals(&mirror_termios);
	while (true)
	{
		cmd = readline("minishell> ");
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
		if (isatty(STDIN_FILENO))
			add_history(cmd);
		cli.buffer = cmd;
		cli.buff_size = strlen(cmd);
		cli.cur_pos = INIT_SRC_POS;
		parse_and_execute(&cli);
		free(cmd);
	}
	rl_clear_history();
	exit(EXIT_SUCCESS);
}

int	parse_and_execute(t_cli *cli)
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
		return (1);
	execc(ast_cmd);
	return (0);
}

// void	print_ast(t_node *node, int indent)
// {
// 	t_node	*child;
// 	int		i;
// 	if (node == NULL)
// 		return ;
// 	i = 0;
// 	while ( i < indent - 1)
// 	{
// 		printf("%s  │%s", BLU, RESET);
// 		i++;
// 	}
// 	if (indent > 0)
// 		printf("%s  ├─%s", CYN, RESET);
// 	printf("%sValue: %s%s,%s	%slevel: %s%u%s\n", GRN, YEL,
			// node->val.str, RESET,
// 			RED, YEL, node->type, RESET);
// 	child = node->first_child;
// 	while (child != NULL)
// 	{
// 		print_ast(child, indent + 1);
// 		child = child->next_sibling;
// 	}
// }
