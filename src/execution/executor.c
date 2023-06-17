/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 01:57:47 by asioud            #+#    #+#             */
/*   Updated: 2023/06/18 00:49:37 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int setup_redirections(t_node *node)
{
    int fd;
    int flags = 0;
    int std_fd = -1;
    t_node *child = node->first_child;

    while (child)
    {
        if (child->type == NODE_INPUT || child->type == NODE_OUTPUT || child->type == NODE_APPEND || child->type == NODE_HEREDOC)
        {


            if (child->type == NODE_INPUT)
            {
                flags = O_RDONLY;
                std_fd = STDIN_FILENO;
            }
            else if (child->type == NODE_OUTPUT)
            {
                flags = O_WRONLY | O_CREAT | O_TRUNC;
                std_fd = STDOUT_FILENO;
            }
            else if (child->type == NODE_APPEND)
            {
                flags = O_WRONLY | O_CREAT | O_APPEND;
                std_fd = STDOUT_FILENO;
            }
 
            if (child->first_child && child->first_child->val.str)
            {
                fd = open(child->first_child->val.str, flags, 0644);
                if (fd == -1)
                {
                    perror("open");
                    return 1;
                }

                if (dup2(fd, std_fd) == -1)
                {
                    perror("dup2");
                    close(fd);
                    return 1;
                }

                close(fd);
            }
        }
        child = child->next_sibling;
    }

    return 0;
}


/**
 * @brief Waits for a child process to terminate and returns its status.
 * @param child_pid The process ID of the child process.
 * @return The status of the child process.
*/
int wait_for_child(pid_t child_pid)
{
	int status = 0;
	waitpid(child_pid, &status, 0);
	return status;
}

int execute_pipeline(t_node *node)
{
    int pipefd[2];
	pid_t child_pid;
	
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return 1;
    }

    child_pid = fork();
    if (child_pid == -1)
    {
        perror("fork");
        return 1;
    }

    if (child_pid == 0)
    {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execc(node->first_child);
        exit(EXIT_FAILURE);
    }

    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);

    int status = execc(node->first_child->next_sibling);
    wait_for_child(child_pid);
    return status;
}


/**
 * @brief Executes a command with the given arguments.
 * @param argc The number of arguments, including the command itself.
 * @param argv The first element is the command and the rest are the arguments.
 * @return 0 on success, or 1 if an error occurs.
*/
int exec_cmd(int argc, char **argv)
{
	(void)argc;
	if (strchr(argv[0], '/'))
		execv(argv[0], argv);
	else
	{
		char *path = search_path(argv[0]);
		if (!path)
			return (1);
		execv(path, argv);
		free(path);
	}
	return (0);
}



/**
 * @brief Frees the memory allocated for the given arguments.
 * @param argc The number of arguments.
 * @param argv null-terminated strings containing the arguments.
*/
static inline void free_argv(int argc, char **argv)
{
	if (!argc)
		return;
	while (argc--)
		free(argv[argc]);
}

/**
 * @brief Runs a built-in command if it matches the given arguments.
 * @param argc The number of arguments, including the command itself.
 * @param argv A null-terminated strings, where the first element is the 
 * 			command and the rest are its arguments.
 * @return 0 if the built-in command was found and executed,
 * 		or -1 if no matching built-in command was found.
*/
static int run_builtin(int argc, char **argv)
{
	for (int i = 0; i < builtins_count; i++)
	{
		if (strcmp(argv[0], builtins[i].name) == 0)
		{
			builtins[i].func(argc, argv);
			return 0;
		}
	}
	return -1;
}

/**
 * @brief Forks the current process and executes the given command in the
 * 		child process.
 * @param argc The number of arguments, including the command itself.
 * @param argv A null-terminated strings, where the first element is the command
 * 			and the rest are its arguments.
 * @return The process ID of the child process on success,
 * 		or -1 if an error occurs.
*/
static pid_t fork_command(int argc, char **argv, t_node *node)
{
    pid_t child_pid = fork();
    if (child_pid == 0)
    {
        if (setup_redirections(node) == 0)
        {
            exec_cmd(argc, argv);
        }
        fprintf(stderr, "error: failed to execute command: %s\n", strerror(errno));
        if (errno == ENOEXEC)
            exit(126);
        else if (errno == ENOENT)
            exit(127);
        else
            exit(EXIT_FAILURE);
    }
    return child_pid;
}

/**
 * @brief Parses the command arguments from a node tree and stores them in an
 * 		array of strings.
 * @param node A pointer to a t_node struct representing the command node.
 * @param argc To store the number of arguments.
 * @param targc To Store the Total number of arguments.
 * @param argv A null-terminated strings that will store the arguments.
 * @return 0 on success, or a non-zero value if an error occurs.
*/
static int parse_arguments(t_node *node, int *argc, int *targc, char ***argv)
{
	struct s_word	*w;
	struct s_word	*w2;
	t_node			*child = node->first_child;
	char			*str;
	char			*arg;
	
	while (child)
	{
		str = child->val.str;
		if (child->type == NODE_INPUT || child->type == NODE_OUTPUT || child->type == NODE_APPEND || child->type == NODE_HEREDOC)
            break;
		w = expand(str);
		if (!w)
		{
			child = child->next_sibling;
			continue;
		}
		w2 = w;
		while (w2)
		{
			if (check_buffer_bounds(argc, targc, argv))
			{
				arg = malloc(strlen(w2->data) + 1);
				if (arg)
				{
					strcpy(arg, w2->data);
					(*argv)[(*argc)++] = arg;
				}
			}
			w2 = w2->next;
		}
		free_all_words(w);
		child = child->next_sibling;
	}
	if (check_buffer_bounds(argc, targc, argv))
		(*argv)[(*argc)] = NULL;
	return 0;
}

/**
 * @brief Executes a command represented by a node tree.
 * @param node A pointer to a t_node struct representing the command node.
 * @return 0 on success, or 1 if an error occurs.
 *
 * This function parses the arguments from the node tree, checks for built-in
 * commands, and forks the current process to execute the command. It waits for
 * the child process to terminate and returns its status.
*/
int execc(t_node *node)
{
	char	**argv = NULL;
	int		argc = 0;
	int		targc = 0;
	pid_t	child_pid;
	int		status;

    if (!node)
        return 1;

	if (node->type == NODE_ASSIGNMENT)
    {
		string_to_symtab(node->first_child->val.str);
        return 0;
	}
	

    if (node->type == NODE_PIPE)
    {
        int original_stdin = dup(STDIN_FILENO);
        int pipeline_status = execute_pipeline(node);
        dup2(original_stdin, STDIN_FILENO);
        close(original_stdin);

        return pipeline_status;
    }
	
	if (parse_arguments(node, &argc, &targc, &argv) != 0 || !node)
		return (1);


    if (setup_redirections(node) != 0)
    {
        free_argv(argc, argv);
        return 1;
    }
    
	if (run_builtin(argc, argv) == 0)
	{
		free_argv(argc, argv);
		return (0);
	}
    
	child_pid = fork_command(argc, argv, node);

	if (child_pid == -1)
	{
		fprintf(stderr, "error: failed to fork command: %s\n", strerror(errno));
		free_argv(argc, argv);
		return (1);
	}
	
	status = wait_for_child(child_pid);
	free_argv(argc, argv);
	return (status == 0 ? 0 : 1);
}

