/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 21:40:34 by AleXwern          #+#    #+#             */
/*   Updated: 2021/11/01 23:29:29 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <stdio.h>

int		main(void)
{
	char *str1 = (char*)malloc(13);
	char *str2 = (char*)malloc(1300);
	char *str3 = (char*)malloc(1300);
	char *str4 = (char*)malloc(1300);
	char *str5 = (char*)malloc(13);
	ft_memcpy(str1, "abcdefghijk", 12);
	//show_alloc_mem();
	free(str1);
	free(str2);
	free(str3);
	free(str4);
	free(str5);
	//str3 = (char*)realloc(str3, 2625);
	//printf("Mallocs\n%lx\n%lx\n", str, str2);
	//printf("%d and %d\n", str, str2);
	show_alloc_mem_ex();
	return (0);
}
