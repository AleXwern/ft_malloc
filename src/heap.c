/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 15:43:34 by AleXwern          #+#    #+#             */
/*   Updated: 2021/10/18 16:10:22 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static t_heap			*get_free_heap(size_t size)
{
	t_heap				*heap_needle;

	heap_needle = g_heap;
	while (heap_needle)
	{
		if (heap_needle->free_size >= size)
			break;
		heap_needle = heap_needle->next;
	}
	return (heap_needle);
}

t_heap					*get_heap(size_t size)
{
	t_heap				*heap;

	heap = get_free_heap(size + sizeof(t_block));
	if (!heap)
	{
		if (!(heap = mmap_new_area(size)))
			return (NULL);
		heap->next = g_heap;
		g_heap = heap;
	}
	return (heap);
}
