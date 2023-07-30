/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 11:22:52 by asioud            #+#    #+#             */
/*   Updated: 2023/07/03 17:38:55 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# define EXPORT "bash: export: --: invalid option\nexport: \
        usage: export [-nf] [name[=value] ...] or export -p\n"

typedef struct s_env
{
	char				*value;
	struct s_env		*next;
}						t_env;

struct					s_builtin
{
	char				*name;
	int					(*func)(int argc, ...);
};
typedef struct s_builtin_info
{
	struct s_builtin	*builtins;
	int					count;
}						t_builtin_info;

int						exec_builtin(int argc, char **argv);
int						ft_exit(int argc, ...);
int						ft_unset(int argc, ...);
int						ft_echo(int argc, ...);
int						ft_env(int argc, ...);
int						ft_pwd(int argc, ...);
int						ft_cd(int argc, ...);
int						ft_export(int argc, ...) __attribute__((unused));

t_builtin_info			*get_bt(void);

#endif
