/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 20:11:48 by AleXwern          #+#    #+#             */
/*   Updated: 2021/10/14 22:01:52 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void			get_free_block(t_block **block, t_heap **heap, size_t size)
{
	t_heap			*heap_needle;
	t_block			*block_needle;
	
	heap_needle = g_heap;
	while (heap_needle)
	{
		block_needle = (void*)heap_needle + sizeof(t_heap);
		while (block_needle)
		{
			if (!block_needle->free &&
				block_needle->data_size >= (size + sizeof(t_block)))
			{
				*heap = heap_needle;
				*block = block_needle;
				return;
			}
			block_needle = block_needle->next;
		}
		heap_needle = heap_needle->next;
	}
	*heap = NULL;
	*block = NULL;
}

static void			set_new_block(t_heap *heap, t_block *block, size_t size)
{
	t_block			*null_block;

	null_block = (void*)block + size;
	null_block->next = NULL;
	null_block->prev = block;
	null_block->free = 1;
	null_block->data_size = heap->free_size - size;
	block->next = null_block;
	block->free = 0;
	block->data_size = size;
}

t_block				*try_fill_allocated_space(size_t size)
{
	t_block			*block;
	t_heap			*heap;

	get_free_block(&block, &heap, size);
	if (block)
	{
		set_new_block(heap, block, size);
		return (block);
	}
	return (block);
}

void				*create_new_block(t_heap *heap, size_t size)
{
	t_block			*block;
	t_block			*last;

	last = NULL;
	block = ((void*)heap) + sizeof(t_heap);
	if (heap->block_count)
	{
		last = get_last_block(heap);
		block = ((void*)heap) + sizeof(t_heap) + last->data_size;
		last->next = block;
	}
	block->data_size = size;
	block->free = 0;
	block->next = NULL;
	heap->block_count++;
	heap->free_size -= (sizeof(t_block) + block->data_size);
	return(block + 1);
}
