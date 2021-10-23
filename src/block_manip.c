/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_manip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 13:11:56 by AleXwern          #+#    #+#             */
/*   Updated: 2021/10/23 15:55:25 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
**	If the next block is free, merge that block into this block.
**	If the previous block is free, merge this block into it.
**	This makes sure that continuous free blocks are merged so further
**	allocations don't need to deal with multiple blocks at once or in case
**	of free we can tell if the entire zone should be munmapped afterwards.
*/

void		merge_blocks(t_heap *heap, t_block *block)
{
	if (block)
	{
		block->free = 1;
		heap->free_size += sizeof(t_block) + block->data_size;
		heap->block_count--;
		if (block->next && block->next->free)
		{
			block->data_size += sizeof(t_block) + block->next->data_size;
			if (block->next->next)
				block->next->next->prev = block;
			block->next = block->next->next;
		}
		if (block->prev && block->prev->free)
		{
			block->prev->data_size += sizeof(t_block) + block->data_size;
			if (block->next)
				block->next->prev = block->prev;
			block->prev->next = block->next;
		}
	}
}

/*
**	Following 2 are realloc step when we are expaning the area of a block.
**	First we try to extend the current block's area forward, shrink and push
**	the following block's area and meta and update all the information to
**	reflect the changes. The XOR of aimsize is just a very very small
**	optimization trick.
**
**	If we can't push the area forward, well check if the previous area is free
**	and merge the entire block there and copy the area from old area to new area.
*/

t_block		*try_move_block(t_heap *heap, t_block *block, size_t aimsize)
{
	if (aimsize && block->prev && block->prev->free && 
			block->prev->data_size >= aimsize)
	{
		block->prev->data_size += block->data_size + sizeof(t_block);
		block->prev->next = block->next;
		if (block->next)
			block->next->prev = block->prev;
		ft_memcpy(block->prev + 1, block + 1, block->data_size);
		return (block->prev);
	}
	return (block);
}

t_block		*try_extend_block(t_heap *heap, t_block *block, size_t aimsize)
{
	if (block->next && block->next->free && block->next->data_size >= aimsize)
	{
		block->data_size += aimsize;
		block->next->data_size -= aimsize;
		ft_memcpy((void*)block->next + aimsize, block->next, sizeof(t_block));
		block->next = (void*)block->next + aimsize;
		if (block->next->next)
			block->next->next->prev = block->next;
		aimsize ^= aimsize;
	}
	return (try_move_block(heap, block, aimsize));
}

/*
**	Realloc step if we are trying to shrink the currently allocated block.
**	The only real special condition is that we need to be able to fit
**	the header into the to-be-free space. If we can't, we won't shrink the size.
**	In most cases the shrink will happen and the only special case is if we are
**	shrinking by only 16 bytes (size of block header is 32 in 64-bit machine).
*/

void		shrink_block(t_heap *heap, t_block *block, size_t size)
{
	size_t	diff;
	t_block	*next;

	if (block->next->free && block->data_size - size < sizeof(t_block))
		return;
	diff = block->data_size - size - sizeof(t_block);
	block->data_size = size;
	next = (void*)block + sizeof(t_block) + size;
	next->data_size = diff;
	next->next = block->next;
	if (block->next)
		block->next->prev = next;
	block->next = next;
	next->prev = block;
	merge_blocks(heap, next);
	heap->block_count++;
}
