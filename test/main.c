/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 21:40:34 by AleXwern          #+#    #+#             */
/*   Updated: 2021/10/14 23:32:24 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <stdio.h>

int		main(void)
{
	char *str = (char*)malloc(1);
	char *str2 = (char*)malloc(1);
	//printf("Mallocs\n%lx\n%lx\n", str, str2);
	show_alloc_mem();
	return (0);
}
