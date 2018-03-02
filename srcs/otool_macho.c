/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_macho.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 18:48:27 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/02 20:00:57 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static size_t	otool_macho_items(const char *fileraw, const size_t flags)
{
	if (flags & OTOOL_FLAG_64BITS)
		return (((struct mach_header_64 *)(size_t)fileraw)->ncmds);
	if (flags & OTOOL_FLAG_32BITS)
		return (((struct mach_header *)(size_t)fileraw)->ncmds);
	return (0);
}

size_t			otool_macho(char *fileraw, size_t filesize, size_t flags)
{
	struct load_command		*lc;
	size_t					i;
	const size_t			ncmds = otool_macho_items(fileraw, flags);

	lc = (void*)&fileraw[flags & OTOOL_FLAG_64BITS ?
		sizeof(struct mach_header_64) : sizeof(struct mach_header)];
	i = 0;
	while (i < ncmds)
	{
		if (otool_security(fileraw, filesize, lc) != OTOOL_FLAG_OK)
		{
			flags |= OTOOL_FLAG_ERROR;
			break ;
		}
		if (lc->cmd == LC_SYMTAB)
			;
		else if (lc->cmd == LC_SEGMENT_64)
			ft_printf("seg 64 found\n");
		else if (lc->cmd == LC_SEGMENT)
			ft_printf("seg 32 found\n");
		lc = (void*)((size_t)lc + lc->cmdsize);
		i++;
	}
	return (flags);
}
