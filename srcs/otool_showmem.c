/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_showmem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 21:29:56 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/05 14:27:14 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static inline void	otool_showmem_rest(const unsigned char *ptr,
	const unsigned char *lastptr, const size_t offset, const size_t padding)
{
	ft_printf("%0*lx\t", padding, offset);
	while (ptr < lastptr)
		ft_printf("%02x ", *(ptr++));
	ft_putchar('\n');
}

void				otool_showmem(const unsigned char *ptr,
	const size_t size, const size_t offset, const size_t flags)
{
	const unsigned char		*lastptr = &ptr[size];
	size_t					pos;
	const size_t			padding = (flags & FLAG_32BITS) ? 8 : 16;

	pos = 0;
	while ((ptr < lastptr) && (size - pos >= 16))
	{
		ft_printf("%0*lx\t%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x"
			" %02x %02x %02x %02x %02x %02x \n",
			padding,
			pos + offset, ptr[0], ptr[1], ptr[2], ptr[3], ptr[4], ptr[5],
			ptr[6], ptr[7], ptr[8], ptr[9], ptr[10], ptr[11], ptr[12], ptr[13],
			ptr[14], ptr[15]);
		ptr += 16;
		pos += 16;
	}
	if (ptr < lastptr)
		otool_showmem_rest(ptr, lastptr, pos + offset, padding);
}
