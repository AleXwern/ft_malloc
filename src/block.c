/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 20:11:48 by AleXwern          #+#    #+#             */
/*   Updated: 2021/10/23 16:09:09 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
**	Following 3 functions are part of the first step of malloc.
**	Malloc quickly allocates memory by pre-allocating a bigger chunk. Here we
**	try to locate one of those chunks and then split it into smaller blocks
**	which we return a pointer to. Vast majority of malloc calls should only
**	go through this step and this step is way faster than calling mmap.
*/

static t_block		*get_free_block(t_heap **heap, size_t size)
{
	t_heap			*heap_needle;
	t_block			*block_needle;
	t_uint8			type;
	
	heap_needle = g_heap;
	type = (size > HEAP_TINY) + (size > HEAP_SMALL);
	while (heap_needle)
	{
		block_needle = (void*)heap_needle + sizeof(t_heap);
		while (block_needle && type == heap_needle->group)
		{
			if (block_needle->free &&
				block_needle->data_size >= (size + sizeof(t_block)))
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

static void			set_new_block(t_heap *heap, t_block *block, size_t size)
{
	t_block			*null_block;

	null_block = (void*)block + sizeof(t_block) + size;
	null_block->next = NULL;
	null_block->prev = block;
	null_block->free = 1;
	null_block->data_size = block->data_size - (sizeof(t_block) + size);
	block->next = null_block;
	block->free = 0;
	block->data_size = size;
	heap->block_count++;
	heap->free_size -= size + sizeof(t_block);
}

t_block				*try_fill_allocated_space(size_t size)
{
	t_block			*block;
	t_heap			*heap;

	if (block = get_free_block(&heap, size))
		set_new_block(heap, block, size);
	return (block);
}

/*
**	
*/

t_block				*create_null_block(t_block *block, size_t size)
{
	if (size < sizeof(t_block))
		return (NULL);
	block->next = NULL;
	block->free = 1;
	block->data_size = size;
	return (block);
}

void				*create_new_block(t_heap *heap, size_t size)
{
	t_block			*block;

	block = ((void*)heap) + sizeof(t_heap);
	block->data_size = size;
	block->free = 0;
	heap->block_count++;
	heap->free_size -= (sizeof(t_block) + block->data_size);
	block->next = create_null_block(
		(void*)block + sizeof(t_block) + block->data_size,
		heap->free_size);
	if (!block->next)
		return (NULL);
	block->next->prev = block;
	return(block + 1);
}
