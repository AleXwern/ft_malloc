/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:09:56 by AleXwern          #+#    #+#             */
/*   Updated: 2021/10/14 22:44:42 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
**	From "man malloc":
**	The malloc() function allocates size bytes and returns a pointer to the allocated memory.  The memory is not initialized.  If size is 0, then malloc() returns either NULL, or a unique pointer value that can later be
**	successfully passed to free().
**
**	The malloc() and calloc() functions return a pointer to the allocated memory, which is suitably aligned for any built-in type.  On error, these functions return NULL.  NULL may also be returned by a successful  call
**	to malloc() with a size of zero, or by a successful call to calloc() with nmemb or size equal to zero.
**
**	calloc(), malloc(), realloc(), and reallocarray() can fail with the following error:
**	ENOMEM Out of memory.  Possibly, the application hit the RLIMIT_AS or RLIMIT_DATA limit described in getrlimit(2).
*/

/*
**	Documentation:
**	Malloc is essentially a wrapper around syscall 9 aka mmap. Calling syscalls is very heavy
**	so we need to make a compromise with either memory or performance.
**	With malloc it's memory. We allocate a great chunck of memory the first time we call malloc
**	and then we split the chunck into smaller blocks. Very simply put the first call is the heaviest
**	since we are always calling mmap there and most malloc calls afterwards are very light since we are
**	just doing a simple split of already allocated space and returning a valid pointer.
**
**	How is this done? I the core we have 3 types of base allocations: TINY, SMALL and LARGE.
**	We'll call these "heap" and they always have a "heap metadata" at the start containing info
**	about them. The global variable g_heap is a linked list of these heap metadatas.
**	These heap are split into blocks and the blocks too have a metadata about them at the start of the block.
**	The first block metadata is directly after the heap metadata so we don't need to direcly track
**	where the blocks are from heap data but blocks do track each other. This is to save memory as much as possible.
**	The data after block metadata is the data user is asking for and such the returned pointer
**	is to the first byte after block metadata.
**	The allocations are also always rounded up to the next word to fill MacOS standard. You ask for 1 byte and you get 16.
*/

static inline void	*malloc_base(size_t size)
{
	void 			*ptr;
	t_heap			*heap;
	t_block			*block;

	if (!size)
		return (NULL);
	size = (size + 15) & ~15;
	if (block = try_fill_allocated_space(size))
		return (block + 1);
	if (!(heap = get_heap(size)))
		return (NULL);
	ptr = create_new_block(heap, size);
	return (ptr);
}

void				*malloc(size_t size)
{
	void			*ptr;

	pthread_mutex_lock(&g_malloc_mutex);
	ptr = malloc_base(size);
	pthread_mutex_unlock(&g_malloc_mutex);
	return (ptr);
}
