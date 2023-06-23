/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asioud <asioud@42heilbronn.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 03:32:19 by asioud            #+#    #+#             */
/*   Updated: 2023/06/23 18:12:28 by asioud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_memory_block
{
	void					*adresse;
	size_t					size;
	struct s_memory_block	*next;
}				t_memory_block;

void	*add_mem_block(void **p_head, size_t size);
void	remove_mem_block(void **p_head, void *ptr);
void	*my_malloc(void **p_head, size_t size);
void	my_free(void **p_head, void *adresse);
void	free_all_mem(void **p_head);
void	display_memory(void *p_head);
#endif