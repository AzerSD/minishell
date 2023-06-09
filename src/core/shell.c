/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 01:45:52 by asioud            #+#    #+#             */
/*   Updated: 2023/06/09 18:17:30 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./shell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <termios.h>
#include "../signals/signals.h"

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
		/* Handle Signals */
		// signal(SIGINT, handle_sigint);
		// signal(SIGQUIT, handle_sigquit);
		/* Our PS */
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
			exit_builtin(1, 0);
		}
		/* If it is a terminal not running by a script or smth*/
		if (isatty(STDIN_FILENO))
			add_history(cmd);
		/* Init Command Line Struct */
		cli.buffer = cmd;
		cli.buff_size = strlen(cmd);
		cli.cur_pos = INIT_SRC_POS;
		parse_and_execute(&cli);
		free(cmd);
	}
	clear_history();
	exit(EXIT_SUCCESS);
}

int	parse_and_execute(t_cli *cli)
{
	t_node		*cmd;
	t_token		*tok;
	t_curr_tok	*curr;

	curr = malloc(sizeof(t_curr_tok));
	skip_whitespaces(cli);
	tok = get_token(cli, curr);
	while (tok && tok != EOF_TOKEN)
	{
		cmd = parse_cmd(tok, curr);
		if (!cmd)
			break ;
		execc(cmd);
		free_node_tree(cmd);
		tok = get_token(cli, curr);
	}
	return (0);
}
