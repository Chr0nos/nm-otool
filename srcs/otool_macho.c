/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_macho.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 18:48:27 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/02 20:13:52 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static size_t	otool_macho_items(const char *fileraw, const size_t flags)
{
	size_t			size;

	size = 0;
	if (flags & OTOOL_FLAG_64BITS)
		size = ((struct mach_header_64 *)(size_t)fileraw)->ncmds;
	if (flags & OTOOL_FLAG_32BITS)
		size = ((struct mach_header *)(size_t)fileraw)->ncmds;
	if (flags & OTOOL_FLAG_CIGAM)
		return (swap64(size));
	return (size);
}

static void		otool_macho_init(char *fileraw, const size_t flags,
	struct load_command **lc, t_list **segments)
{
	*lc = (void*)&fileraw[flags & OTOOL_FLAG_64BITS ?
		sizeof(struct mach_header_64) : sizeof(struct mach_header)];
	*segments = NULL;
}

size_t			otool_macho(char *fileraw, size_t filesize, size_t flags)
{
	struct load_command		*lc;
	size_t					i;
	const size_t			ncmds = otool_macho_items(fileraw, flags);
	t_list					*segments;

	otool_macho_init(fileraw, flags, &lc, &segments);
	i = 0;
	while (i++ < ncmds)
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
	}
	ft_lstdel(&segments, NULL);
	return (flags);
}
