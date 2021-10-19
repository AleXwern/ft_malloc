/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:13:27 by AleXwern          #+#    #+#             */
/*   Updated: 2021/10/19 14:12:51 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void			error_out(void)
{
	ft_putendl("Free error!");
	exit(1);
}

void			free(void *ptr)
{
	t_block		*block;
	t_heap		*heap;
	
	pthread_mutex_lock(&g_malloc_mutex);
	if (ptr)
	{
		if (!(block = match_block(&heap, ptr)))
			error_out();
		merge_blocks(heap, block);
		if (!heap->block_count)
			munmap_heap(heap);
	}
	pthread_mutex_unlock(&g_malloc_mutex);
}
