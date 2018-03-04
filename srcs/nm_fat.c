/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_fat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 02:53:00 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/04 15:49:43 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "arch_lookup.h"

void					nm_fat_run(struct fat_arch *arch, t_common *com)
{
	t_nm		*nm;
	t_nm		sub;

	nm = (void*)com;
	sub = *nm;
	sub.flags &= ~FLAG_CIGAM;
	sub.flags |= FLAG_FAT;
	sub.fileraw = &nm->fileraw[arch->offset];
	sub.filesize -= arch->offset;
	sub.magic = *(unsigned int *)(size_t)sub.fileraw;
	handle_files_types(&sub);
	nm->flags |= FLAG_SYMTAB;
}
