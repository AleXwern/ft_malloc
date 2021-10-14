/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:13:27 by AleXwern          #+#    #+#             */
/*   Updated: 2021/10/12 19:14:40 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void			free(void *ptr)
{
	if (!ptr)
		return ;
	pthread_mutex_lock(&g_malloc_mutex);
	pthread_mutex_unlock(&g_malloc_mutex);
}
