/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_macho.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 18:48:27 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/03 02:48:29 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void			otool_macho_symtab(const size_t ptr, t_list *segments,
	t_common *com)
{
	struct symtab_command		*sym;
	char						*stringtable;
	struct segment_command_64	*seg;

	com->flags |= FLAG_SYMTAB;
	sym = (void*)ptr;
	stringtable = (char*)(ptr + sym->symoff);
	while ((segments) && (!(com->flags & FLAG_ERROR)))
	{
		seg = segments->content;
		if (!security(com, seg, segments->content_size))
		{
			ft_printf("%p -> %12s\n", seg, seg->segname);
		}
		segments = segments->next;
	}
}
