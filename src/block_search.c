/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_search.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 21:09:28 by AleXwern          #+#    #+#             */
/*   Updated: 2021/10/15 12:33:40 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_block			*get_last_block(t_heap *heap)
{
	t_block		*block;
	size_t		i;

	block = ((void*)heap) + sizeof(t_heap);
	while (i < heap->block_count - 1)
		block = block->next;
	return (block);
}

t_block			*match_block(t_heap **heap, void *ptr)
{
	t_heap		*heap_needle;
	t_block		*block_needle;
	
	heap_needle = g_heap;
	while (heap_needle)
	{
		block_needle = (void*)heap_needle + sizeof(t_heap);
		while (block_needle)
		{
			if ((void*)block_needle + sizeof(t_block) == ptr)
			{
				*heap = heap_needle;
				return (block_needle);
			}
			block_needle = block_needle->next;
		}
		heap_needle = heap_needle->next;
	}
	*heap = NULL;
	return (NULL);
}
