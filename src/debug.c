/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 22:08:08 by AleXwern          #+#    #+#             */
/*   Updated: 2021/11/01 22:45:48 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void	print_heap_info(t_heap *heap)
{
	ft_putstr("HEAP data at: 0x");
	ft_puthexln((long)heap);
	if (!heap->group)
		ft_putendl("Group: TINY");
	else if (heap->group == 1)
		ft_putendl("Group: SNALL");
	else
		ft_putendl("Group: LARGE");
	ft_putstr("Total size: ");
	ft_putnbrln(heap->total_size);
	ft_putstr("Free size: ");
	ft_putnbrln(heap->free_size);
	ft_putstr("Reserved blocks: ");
	ft_putnbrln(heap->block_count);
}

static void	print_block_info(t_heap *heap, char ex)
{
	t_block *block;

	block = (void*)heap + sizeof(t_heap);
	while (block)
	{
		ft_putstr("->BLOCK data at: 0x");
		ft_puthexln((long)block);
		ft_putstr("  Total size: ");
		ft_putulongln(block->data_size);
		ft_putstr("  Is free?: ");
		ft_puthexln(block->free);
		if (ex && !block->free)
			print_hex_dump(block);
		block = block->next;
	}
}

/*
**	This single function is major reason I wanted to do this project. I love it!
*/
void		show_alloc_mem(void)
{
	t_heap	*heap;

	pthread_mutex_lock(&g_malloc_mutex);
	heap = g_heap;
	if (!heap)
	{
		ft_putendl("No memory allocated!");
		return ;
	}
	while (heap->next)
		heap = heap->next;
	while (heap)
	{
		print_heap_info(heap);
		print_block_info(heap, 0);
		heap = heap->prev;
	}
	pthread_mutex_unlock(&g_malloc_mutex);
}

void		show_alloc_mem_ex(void)
{
	t_heap	*heap;

	pthread_mutex_lock(&g_malloc_mutex);
	heap = g_heap;
	if (!heap)
	{
		ft_putendl("No memory allocated!");
		return ;
	}
	while (heap->next)
		heap = heap->next;
	while (heap)
	{
		print_heap_info(heap);
		print_block_info(heap, 1);
		heap = heap->prev;
	}
	pthread_mutex_unlock(&g_malloc_mutex);
}
