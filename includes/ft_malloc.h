/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:07:45 by AleXwern          #+#    #+#             */
/*   Updated: 2022/06/20 18:01:28 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

#ifdef __cplusplus
extern "C" {
#endif

# include <sys/mman.h>
# include <sys/resource.h>
# include <pthread.h>
//# include <stdlib.h>
# include "libft.h"

# define MAGIC_NUMBER		32
# define ALIGN				16
# define HEXDUMP			ALIGN * 3
# ifndef FT_PAGE_DEFINED
#  define HEAP_TINY			(getpagesize() * MAGIC_NUMBER)
#  define HEAP_SMALL		(getpagesize() * MAGIC_NUMBER * 8)
# else
#  define HEAP_TINY			(FT_PAGE_DEFINED * MAGIC_NUMBER)
#  define HEAP_SMALL		(FT_PAGE_DEFINED * MAGIC_NUMBER * 8)
# endif

# ifdef NEVER_DEFINED
#define PROT_READ	0x1		/* Page can be read.  */
#define PROT_WRITE	0x2		/* Page can be written.  */
#define PROT_EXEC	0x4		/* Page can be executed.  */
#define PROT_NONE	0x0		/* Page can not be accessed.  */
#define PROT_GROWSDOWN	0x01000000	/* Extend change to start of growsdown vma (mprotect only).  */
#define PROT_GROWSUP	0x02000000	/* Extend change to start of growsup vma (mprotect only).  */
/* Sharing types (must choose one and only one of these).  */
#define MAP_SHARED	0x01		/* Share changes.  */
#define MAP_PRIVATE	0x02		/* Changes are private.  */
# define MAP_SHARED_VALIDATE	0x03	/* Share changes and validate extension flags.  */
# define MAP_TYPE	0x0f		/* Mask for type of mapping.  */
#define MAP_FIXED	0x10		/* Interpret addr exactly.  */
# define MAP_FILE	0
#  define MAP_ANONYMOUS	0x20		/* Don't use a file.  */
# define MAP_ANON	MAP_ANONYMOUS
# endif

# define BLOCK_TINY			(HEAP_TINY / 128)
# define BLOCK_SMALL		(HEAP_SMALL / 128)

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
void					*calloc(size_t nmemb, size_t size);
void					free(void *ptr);
void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);
void					show_alloc_mem(void);
void					show_alloc_mem_ex(void);

void					free_base(void *ptr);
void					*malloc_base(size_t size);

/*
**	Handler functions.
*/
t_block					*get_last_block(t_heap *heap);
t_block					*match_block(t_heap **heap, void *ptr);
t_block					*try_extend_block(t_heap *heap, t_block *block, size_t aimsize);
t_block					*try_fill_allocated_space(size_t size);

t_heap					*get_heap(size_t size);
t_heap					*mmap_new_area(size_t size);

void					*create_new_block(t_heap *heap, size_t size);
void					error_out(void);
void					merge_blocks(t_heap *heap, t_block *block);
void					munmap_heap(t_heap *heap);
void					print_hex_dump(t_block *block);
void					shrink_block(t_heap *heap, t_block *block, size_t size);

#ifdef __cplusplus
}
#endif

#endif
