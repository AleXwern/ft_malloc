/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 20:11:44 by AleXwern          #+#    #+#             */
/*   Updated: 2021/10/14 22:02:24 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

size_t		get_real_heapsize(size_t size)
{
	if (size > HEAP_SMALL)
		return (size + sizeof(t_heap) + sizeof(t_block));
	else if (size > HEAP_TINY)
		return (HEAP_SMALL);
	return (HEAP_TINY);
}

t_heap		*mmap_new_area(size_t size)
{
	t_heap	*heap;
	size_t	realsize;

	realsize = get_real_heapsize(size);
	heap = mmap(NULL, realsize, PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE, -1, 0);
	if (heap == ((void*)-1))
		return (NULL);
	heap->block_count = 0;
	heap->free_size = realsize - sizeof(t_heap);
	heap->prev = NULL;
	heap->next = NULL;
	heap->total_size = heap->free_size;
	return (heap);
}
