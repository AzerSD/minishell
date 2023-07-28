/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 01:45:52 by asioud            #+#    #+#             */
/*   Updated: 2023/07/28 21:46:47 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*init_main(int argc, char **argv, char **env,
		struct termios *mirror_termios)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = malloc(sizeof(t_shell));
	shell->memory = NULL;
	init_symtab(env);
	shell->status = 0;
	signals(mirror_termios);
	return (shell);
}

t_cli	init_cli(char *cmd)
{
	t_cli	cli;

	cli.buffer = cmd;
	cli.buff_size = strlen(cmd);
	cli.cur_pos = INIT_SRC_POS;
	return (cli);
}

void	main_loop(t_shell *shell)
{
	t_cli	cli;
	char	*cmd;
	int		original_stdout;

	original_stdout = dup(STDOUT_FILENO);
	while (true)
	{
		if (isatty(fileno(stdin)))
			cmd = readline(MAG "minishell> " RESET);
		else
		{
			cmd = get_next_line(fileno(stdin));
			cmd = ft_strtrim(cmd, "\n");
		}
		if (!cmd)
			exit(shell->status);
		if (strncmp(cmd, "exit", 5) == 0)
		{
			free(cmd);
			free_all_mem(&shell->memory);
			exit(shell->status);
		}
		if (isatty(STDIN_FILENO))
			add_history(cmd);
		cli = init_cli(cmd);
		shell->status = parse_and_execute(&cli);
		dup2(original_stdout, STDOUT_FILENO);
	}
}

int	parse_and_execute(t_cli *cli)
{
	t_node		*ast_cmd;
	t_token		*tok;
	t_curr_tok	*curr;

	curr = my_malloc(&shell.memory, sizeof(t_curr_tok));
	skip_whitespaces(cli);
	tok = get_token(cli, curr);
	ast_cmd = parse_cmd(tok, curr);
	if (!ast_cmd)
		return (1);
	return (execc(ast_cmd));
}

int	main(int argc, char **argv, char **env)
{
	struct termios	mirror_termios;
	t_shell			*shell;

	shell = init_main(argc, argv, env, &mirror_termios);
	main_loop(shell);
	rl_clear_history();
	free_all_mem(&shell->memory);
	exit(shell->status);
}
