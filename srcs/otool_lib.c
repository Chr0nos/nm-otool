/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 17:28:07 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/04 17:46:52 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"
#include "lib.h"
#include <ar.h>

void		otool_lib(t_common *com, size_t index,
	const size_t size, t_ar **tab)
{
	t_ar				*pl;
	t_otool				otool;

	while ((index < size) && (!(com->flags & FLAG_ERROR)))
	{
		pl = tab[index++];
		if (!*pl->ar->ar_name)
			continue ;
		ft_memcpy(&otool, com, sizeof(t_otool));
		otool.subfilename = pl->filename;
		otool.fileraw =
			&com->rootraw[pl->offset + sizeof(struct ar_hdr) + pl->len];
		otool.filesize = pl->size;
		otool.flags &= ~MASK_RECUSIVE;
		otool_stack(otool_detect(&otool));
		if (otool.flags & FLAG_ERROR)
			com->flags |= FLAG_ERROR;
		pl->ar->ar_name[0] = '\0';
	}
}
