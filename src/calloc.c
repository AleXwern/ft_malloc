/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 20:11:28 by AleXwern          #+#    #+#             */
/*   Updated: 2021/10/22 15:54:09 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
**	from "man calloc"
**	The  calloc()  function allocates memory for an array of nmemb elements of
**	size bytes each and returns a pointer to the allocated memory.  The memory
**	is set to zero.  If nmemb or size is 0, then calloc() returns either NULL,
**	or a unique pointer value that can later be successfully passed to free().
**	If the multiplication of nmemb and size would result in integer overflow,
**	then calloc() returns an error.  By contrast, an integer overflow would not
**	be detected in the following call to malloc(), with the result that an
**	incorrectly sized block of memory would be allocated:
**		malloc(nmemb * size);
*/

/*
**	Personal notes:
**	Calloc is very similar to malloc. The key difference is that calloc
**	handles *really* big allocations better than standard malloc.
**	Really big in this case means values where nmemb*size overflows.
**	Realistically calloc in that front is only useful in 32-bit machines
**	because of the 4GB memory limit. Commercial 64-bit machines do not have
**	even faction of the memory to even think about 64-bit limits
**	(about 17179869184 gigabytes) so most really big allocations would fail
**	to just general lack of memory.
**	Calloc has other unique attribute that the memory area is zeroed out akin
**	to bzero (man bzero) so the caller can make assumptions what the default
**	data looks like. Default malloc/realloc does not have this attribute.
*/

void		*calloc(size_t nmemb, size_t size)
{
	void			*ptr;
	size_t			total;

	pthread_mutex_lock(&g_malloc_mutex);
	total = nmemb * size;
	if (!total || (total / size) != nmemb)
		return (NULL);
	if (ptr = malloc_base(total))
		ft_bzero(ptr, total);
	pthread_mutex_unlock(&g_malloc_mutex);
	return (ptr);
}
