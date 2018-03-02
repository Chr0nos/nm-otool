/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_macho.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 18:48:27 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/02 21:28:24 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static size_t	otool_macho_items(const t_otool *otool)
{
	size_t			size;

	size = 0;
	if (otool->flags & OTOOL_FLAG_64BITS)
		size = ((struct mach_header_64 *)(size_t)otool->fileraw)->ncmds;
	if (otool->flags & OTOOL_FLAG_32BITS)
		size = ((struct mach_header *)(size_t)otool->fileraw)->ncmds;
	if (otool->flags & OTOOL_FLAG_CIGAM)
		return (swap64(size));
	return (size);
}

static void		otool_macho_symtab(const size_t ptr, t_list *segments,
	const size_t flags)
{
	struct symtab_command		*sym;
	char						*stringtable;
	struct segment_command_64	*seg;

	(void)flags;
	sym = (void*)ptr;
	stringtable = (char*)(ptr + sym->symoff);
	while (segments)
	{
		seg = segments->content;
		ft_printf("%p -> %12s\n", seg, seg->segname);
		segments = segments->next;
	}
}

void			otool_macho(t_otool *otool)
{
	struct load_command		*lc;
	size_t					i;
	const size_t			ncmds = otool_macho_items(otool);

	lc = (void*)&otool->fileraw[otool->flags & OTOOL_FLAG_64BITS ?
		sizeof(struct mach_header_64) : sizeof(struct mach_header)];
	i = 0;
	while (i++ < ncmds)
	{
		if (otool_security(otool, lc) != OTOOL_FLAG_OK)
		{
			otool->flags |= OTOOL_FLAG_ERROR;
			break ;
		}
		if (lc->cmd == LC_SYMTAB)
			otool_macho_symtab((size_t)lc, otool->segments, otool->flags);
		else if (lc->cmd == LC_SEGMENT_64)
			ft_lstadd(&otool->segments, ft_lstnewlink(lc, 64));
		else if (lc->cmd == LC_SEGMENT)
			ft_lstadd(&otool->segments, ft_lstnewlink(lc, 32));
		lc = (void*)((size_t)lc + lc->cmdsize);
	}
	ft_lstdel(&otool->segments, NULL);
}
