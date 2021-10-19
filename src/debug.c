/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 22:08:08 by AleXwern          #+#    #+#             */
/*   Updated: 2021/10/19 14:25:37 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
**	This single function is major reason I wanted to do this project. I love it!
*/
void		show_alloc_mem(void)
{
	t_heap	*heap;
	t_block	*block;
	size_t	i;

	heap = g_heap;
	ft_putstr("Global heapdata: ");
	ft_putnbrln(g_heap);
	while (heap)
	{
		ft_putstr("-> Heap at ");
		ft_putnbrln(heap);
		ft_putstr("Prev: ");
		ft_putnbrln(heap->prev);
		ft_putstr("Next: ");
		ft_putnbrln(heap->next);
		ft_putstr("Total size: ");
		ft_putnbrln(heap->total_size);
		ft_putstr("Free size: ");
		ft_putnbrln(heap->free_size);
		ft_putstr("Blocks: ");
		ft_putnbrln(heap->block_count);
		block = ((void*)heap) + sizeof(t_heap);
		while (block)
		{
			ft_putstr("\n--> Block at ");
			ft_putnbrln(block);
			ft_putstr("-Prev: ");
			ft_putnbrln(block->prev);
			ft_putstr("-Next: ");
			ft_putnbrln(block->next);
			ft_putstr("-Total size: ");
			ft_putnbrln(block->data_size);
			ft_putstr("-Free: ");
			ft_putnbrln(block->free);
			block = block->next;
		}
		heap = heap->next;
	}
}
