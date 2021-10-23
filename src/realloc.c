/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:32:41 by AleXwern          #+#    #+#             */
/*   Updated: 2021/10/23 15:24:16 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
**	We can consider few things from malloc.
*/

static inline void		*realloc_base(void *ptr, size_t size)
{
	t_block		*block;
	t_heap		*heap;
	void		*newptr;
	
	size = (size + 15) & ~15;
	if (!(block = match_block(&heap, ptr)))
		error_out();
	if (block->data_size == size)
		return (ptr);
	newptr = ptr;
	if (size < block->data_size)
		shrink_block(heap, block, size);
	else
	{
		block = try_extend_block(heap, block, size - block->data_size);
		if (block->data_size < size)
		{
			newptr = malloc_base(size);
			if (block->data_size < size)
				size = block->data_size;
			ft_memmove(newptr, block + 1, size);
			merge_blocks(heap, block);
		}
	}
	return (newptr);
}

void					*realloc(void *ptr, size_t size)
{
	pthread_mutex_lock(&g_malloc_mutex);
	if (ptr)
	{
		if (!size)
			free_base(ptr);
		else
			ptr = realloc_base(ptr, size);
	}
	else
		ptr = malloc_base(size);
	pthread_mutex_unlock(&g_malloc_mutex);
	return (ptr);
}
