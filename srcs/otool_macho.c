/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_macho.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 18:48:27 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/04 18:28:44 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static void		otool_macho64(struct segment_command_64 *seg, t_common *com)
{
	const struct section_64		*sec = (void*)((size_t)seg + (sizeof(*seg)));
	size_t						index;
	const size_t				nsects = smartswap64(seg->nsects, com->flags);
	const void					*ptr;

	index = 0;
	while ((index++ < nsects) && (!(com->flags & FLAG_ERROR)))
	{
		if (ft_strcmp(sec->sectname, SECT_TEXT))
			continue ;
		ft_printf("%s%s,%s%s",
			"Contents of (", sec->segname, sec->sectname, ") section\n");
		ptr = &com->fileraw[sec->offset];
		if (!security(com, ptr, sec->size))
			otool_showmem(ptr, sec->size, sec->addr, com->flags);
		break ;
	}
}

static void		otool_macho32(struct segment_command *seg, t_common *com)
{
	const struct section		*sec = (void*)((size_t)seg + (sizeof(*seg)));
	size_t						index;
	const size_t				nsects = smartswap32(seg->nsects, com->flags);
	const void					*ptr;

	if (ft_strcmp(seg->segname, SEG_TEXT))
		return ;
	index = 0;
	while ((index++ < nsects) && (!(com->flags & FLAG_ERROR)))
	{
		if (ft_strcmp(sec->sectname, SECT_TEXT))
			continue ;
		ft_printf("%s%s,%s%s",
			"Contents of (", sec->segname, sec->sectname, ") section\n");
		ptr = &com->fileraw[sec->offset];
		if (!security(com, ptr, sec->size))
			otool_showmem(ptr, sec->size, sec->addr, com->flags);
		break ;
	}
}

void			otool_macho_symtab(const size_t ptr, t_list *segments,
	t_common *com)
{
	struct symtab_command		*sym;
	char						*stringtable;
;
	sym = (void*)ptr;
	stringtable = (char*)(ptr + sym->symoff);
	while ((segments) && (!(com->flags & FLAG_ERROR)))
	{
		if (security(com, segments->content, segments->content_size))
			break ;
		if (segments->content_size == SEGSIZE64)
			otool_macho64(segments->content, com);
		else if (segments->content_size == SEGSIZE32)
			otool_macho32(segments->content, com);
		segments = segments->next;
	}
}
