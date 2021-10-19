/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:07:45 by AleXwern          #+#    #+#             */
/*   Updated: 2021/10/19 14:24:07 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <sys/mman.h>
# include <sys/resource.h>
# include <pthread.h>
# include <stdlib.h>
# include "libft.h"

# define MAGIC_NUMBER		32
# define HEAP_TINY			(getpagesize() * MAGIC_NUMBER)
# define HEAP_SMALL			(getpagesize() * MAGIC_NUMBER * 8)

typedef enum			e_heap_group {
	TINY,
	SMALL,
	LARGE
}						t_heap_group;

// Do I really need prev? It's unnecessary 4/8 bytes and I want to reuse this in
// low memory systems.
// I'll see
typedef struct			s_heap {
	struct s_heap		*prev;
	struct s_heap		*next;
	t_uint8				group;
	size_t				total_size;
	size_t				free_size;
	size_t				block_count;
}						t_heap;

typedef struct			s_block {
	struct s_block		*prev;
	struct s_block		*next;
	size_t				data_size;
	char				free;
}						t_block;

/*
**	As per subject, single global variable to handle allocations
**	and single global variable to make malloc thread safe.
*/
extern pthread_mutex_t	g_malloc_mutex;
extern t_heap			*g_heap;

/*
**	ft_malloc functions.
*/
void					free(void *ptr);
void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);
void					show_alloc_mem(void);

/*
**	Handler functions.
*/
t_block					*get_last_block(t_heap *heap);
t_block					*match_block(t_heap **heap, void *ptr);
t_block					*try_fill_allocated_space(size_t size);

t_heap					*get_heap(size_t size);
t_heap					*mmap_new_area(size_t size);

void					*create_new_block(t_heap *heap, size_t size);
void					merge_blocks(t_heap *heap, t_block *block);
void					munmap_heap(t_heap *heap);

#endif
