/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_fat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 15:54:34 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/04 16:39:26 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void		otool_fat(struct fat_arch *arch, t_common *com)
{
	t_otool		otool;

	otool = *(t_otool*)(void*)com;
	otool.flags &= ~(MASK_TYPE | MASK_ARCH | FLAG_CIGAM);
	otool.flags |= FLAG_RECURSIVE;
	otool.fileraw = &com->fileraw[arch->offset];
	otool.filesize -= arch->offset;
	otool_stack(otool_detect(&otool));
	if (otool.flags & FLAG_ERROR)
		com->flags |= FLAG_ERROR;
}
