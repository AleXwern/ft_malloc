/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 22:08:08 by AleXwern          #+#    #+#             */
/*   Updated: 2021/10/14 23:34:31 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
**	This single function is major reason I wanted to do this project. I love it!
*/
void		show_alloc_mem(void)
{
	ft_putnbrln(g_heap->block_count);
	ft_putnbrln(g_heap->free_size);
	ft_putnbrln(g_heap->total_size);
	ft_putnbrln(g_heap->total_size - g_heap->free_size - (g_heap->block_count * sizeof (t_block)));
}
