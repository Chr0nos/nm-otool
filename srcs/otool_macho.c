/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_macho.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 18:48:27 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/03 02:19:09 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static size_t	otool_macho_items(const t_common *com)
{
	size_t			size;

	size = 0;
	if (com->flags & FLAG_64BITS)
		size = ((struct mach_header_64 *)(size_t)com->fileraw)->ncmds;
	if (com->flags & FLAG_32BITS)
		size = ((struct mach_header *)(size_t)com->fileraw)->ncmds;
	if (com->flags & FLAG_CIGAM)
		return (swap64(size));
	return (size);
}

static void		otool_macho_symtab(const size_t ptr, t_list *segments,
	t_otool *otool)
{
	struct symtab_command		*sym;
	char						*stringtable;
	struct segment_command_64	*seg;

	otool->flags |= FLAG_SYMTAB;
	sym = (void*)ptr;
	stringtable = (char*)(ptr + sym->symoff);
	while ((segments) && (!(otool->flags & FLAG_ERROR)))
	{
		seg = segments->content;
		if (!security((t_common*)otool, seg, segments->content_size))
		{
			ft_printf("%p -> %12s\n", seg, seg->segname);
		}
		segments = segments->next;
	}
}

void			otool_macho(t_otool *otool)
{
	struct load_command		*lc;
	size_t					i;
	const size_t			ncmds = otool_macho_items((t_common*)otool);

	lc = (void*)&otool->fileraw[otool->flags & FLAG_64BITS ?
		sizeof(struct mach_header_64) : sizeof(struct mach_header)];
	i = 0;
	while ((i++ < ncmds) &&
		(!security((t_common*)otool, lc, sizeof(*lc))))
	{
		if (lc->cmd == LC_SYMTAB)
			otool_macho_symtab((size_t)lc, otool->segments, otool);
		else if (lc->cmd == LC_SEGMENT_64)
			ft_lstadd(&otool->segments, ft_lstnewlink(lc, SEGSIZE64));
		else if (lc->cmd == LC_SEGMENT)
			ft_lstadd(&otool->segments, ft_lstnewlink(lc, SEGSIZE32));
		lc = (void*)((size_t)lc + lc->cmdsize);
	}
	ft_lstdel(&otool->segments, NULL);
}
