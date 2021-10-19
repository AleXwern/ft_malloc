/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_manip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 13:11:56 by AleXwern          #+#    #+#             */
/*   Updated: 2021/10/19 14:24:37 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
**	If the next block is free, merge that block into this block.
**	If the previous block is free, merge this block into it.
**	Always return pointer to a created merge or null if that was passed into
**	this function.
*/

void		merge_blocks(t_heap *heap, t_block *block)
{
	if (block)
	{
		block->free = 1;
		heap->free_size += sizeof(t_block) + block->data_size;
		if (block->next && block->next->free)
		{
			block->data_size += sizeof(t_block) + block->next->data_size;
			if (block->next->next)
				block->next->next->prev = block;
			block->next = block->next->next;
			heap->block_count--;
		}
		if (block->prev && block->prev->free)
		{
			block->prev->data_size += sizeof(t_block) + block->data_size;
			if (block->next)
				block->next->prev = block->prev;
			block->prev->next = block->next;
			heap->block_count--;
		}
	}
}
