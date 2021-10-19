/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 21:40:34 by AleXwern          #+#    #+#             */
/*   Updated: 2021/10/19 14:23:33 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <stdio.h>

int		main(void)
{
	char *str = (char*)malloc(130000);
	char *str2 = (char*)malloc(900);
	char *str3 = (char*)malloc(1);
	free(str2);
	free(str);
	free(str3);
	//printf("Mallocs\n%lx\n%lx\n", str, str2);
	//printf("%d and %d\n", str, str2);
	show_alloc_mem();
	return (0);
}
