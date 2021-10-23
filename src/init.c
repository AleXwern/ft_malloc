/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:24:09 by AleXwern          #+#    #+#             */
/*   Updated: 2021/10/19 17:33:01 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
**	As per subject 2 global variables.
**	g_heap is a linked list of heap metadata.
**	g_malloc_mutex is mutex to make memory operations thread safe. It locs all
**	functions if any thread enter any ft_malloc function.
*/

t_heap			*g_heap = NULL;
pthread_mutex_t g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;
