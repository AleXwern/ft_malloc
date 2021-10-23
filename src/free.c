/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:13:27 by AleXwern          #+#    #+#             */
/*   Updated: 2021/10/19 15:48:17 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
**	From: man 3 free
**	The free() function frees the memory space pointed to by ptr,
**	which must have been returned by a previous call to malloc(), calloc(),
**	or realloc().  Otherwise, or if free(ptr) has already been called  before,
**	undefined behavior occurs.  If ptr is NULL, no operation is performed.
*/

/*
**	While doing realloc I noticed I had to split the base malloc and free into 2 parts.
**	Some conditions in realloc act as straight malloc or free and if I want to make
**	this thread safe (the first thing that happens always is locking mutex) I can't
**	call a function that handles locking mutex as I would get a deadlock.
**	In a sense I could do some conditions easier but I also lost some optimization
**	potential which is annoying.
*/
void			error_out(void)
{
	ft_putendl("Free error!");
	exit(1);
}

void			free_base(void *ptr)
{
	t_block		*block;
	t_heap		*heap;

	if (!(block = match_block(&heap, ptr)))
		error_out();
	merge_blocks(heap, block);
	if (!heap->block_count)
		munmap_heap(heap);
}

void			free(void *ptr)
{	
	pthread_mutex_lock(&g_malloc_mutex);
	if (ptr)
		free_base(ptr);
	pthread_mutex_unlock(&g_malloc_mutex);
}
