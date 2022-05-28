/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexdump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 14:17:51 by AleXwern          #+#    #+#             */
/*   Updated: 2021/11/01 23:16:05 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
**	We'll assume that the system is little endian. If it's not then unlucky
**	and I need to do adjustents if that time comes.
**	At least so far even the weirdest systems have been little endian.
*/
static inline void	comp_line(unsigned char *ptr)
{
	char			*hex;
	char			out[HEXDUMP + 2];
	unsigned char	i;

	hex = "0123456789ABCDEF";
	i ^= i;
	((short*)out)[0] = 0x2020;
	while (i < ALIGN)
	{
		out[i * 3 + 2] = hex[ptr[i] >> 4];
		out[i * 3 + 3] = hex[ptr[i] & 0xf];
		out[i * 3 + 4] = ' ';
		i++;
	}
	out[HEXDUMP + 1] = 0xA;
	write(1, out, HEXDUMP + 2);
}

/*
**	Memory allocations have been aligned to 16 bytes so we can
**	use that as length of single line and print hex presentation
**	in sets of 16 bytes.
*/
void				print_hex_dump(t_block *block)
{
	size_t			i;

	i ^= i;
	ft_putendl("  Hexdump of contained data:");
	while (i < block->data_size)
	{
		comp_line((char*)block + sizeof(t_block) + i);
		i += ALIGN;
	}
}
