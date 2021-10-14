/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_search.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 21:09:28 by AleXwern          #+#    #+#             */
/*   Updated: 2021/10/14 21:30:21 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_block			*get_last_block(t_heap *heap)
{
	t_block		*block;
	size_t		i;

	block = ((void*)heap) + sizeof(t_heap);
	while (i < heap->block_count - 1)
		block = block->next;
	return (block);
}
