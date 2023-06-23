/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 01:45:52 by asioud            #+#    #+#             */
/*   Updated: 2023/06/23 17:37:41 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_cli			cli;
	char			*cmd;
	struct termios	mirror_termios;
	int				original_stdout;
	t_memory *mem = malloc(sizeof(t_memory));
	mem->head = NULL;
	// g_status = 0;

	(void)argc;
	(void)argv;
	init_symtab(env);
	signals(&mirror_termios);
	
	// char *s = my_malloc(mem->head, sizeof(char) * 333);
	while (true)
	{
		// cmd = readline("minishell> ");
		if (isatty(fileno(stdin)))
			cmd = readline(MAG"minishell> "RESET);
		else
		{
			cmd = get_next_line(fileno(stdin));
			cmd = ft_strtrim(cmd, "\n");
			free(cmd);
		}
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
	// free_node_tree(ast_cmd);
	return (0);
}

void	print_ast(t_node *node, int indent)
{
	t_node	*child;

	if (node == NULL)
		return ;
	for (int i = 0; i < indent - 1; i++)
		printf("%s  │%s", BLU, RESET);
	if (indent > 0)
		printf("%s  ├─%s", CYN, RESET);
	printf("%sValue: %s%s,%s	%slevel: %s%u%s\n",
			GRN, YEL, node->val.str, RESET,
			RED, YEL, node->type, RESET);

	child = node->first_child;
	while (child != NULL)
	{
		print_ast(child, indent + 1);
		child = child->next_sibling;
	}
}
