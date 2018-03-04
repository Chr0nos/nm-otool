/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_fat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 02:53:00 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/04 15:38:22 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "arch_lookup.h"

static void				show(struct fat_arch *arch)
{
	ft_printf("%s%9d%s%6d%s%6x%s%6x%s%6x%s%6x\n",
		"cpu type: ", arch->cputype,
		" sub type: ", arch->cpusubtype,
		" offset: ", arch->offset,
		" size: ", arch->size,
		" align: ", arch->align,
		" arch: ", (unsigned int)arch->cputype & CPU_ARCH_MASK);
}

static int				fat_run(struct fat_arch *arch, t_nm *nm)
{
	t_nm		sub;

	sub = *nm;
	sub.flags &= ~FLAG_CIGAM;
	sub.flags |= FLAG_FAT;
	sub.fileraw = &nm->fileraw[arch->offset];
	sub.filesize -= arch->offset;
	sub.magic = *(unsigned int *)(size_t)sub.fileraw;
	handle_files_types(&sub);
	nm->flags |= FLAG_SYMTAB;
	return (NM_SUCCESS);
}

void					handle_fat(t_nm *nm)
{
	struct fat_header		*header;
	struct fat_arch			*arch;

	header = (void*)(size_t)nm->fileraw;
	if (security((t_common*)nm, header, sizeof(*header)))
		return ;
	(void)show;
	if (nm->flags & FLAG_CIGAM)
		header->nfat_arch = swap(header->nfat_arch);
	arch = (void*)((size_t)nm->fileraw + sizeof(struct fat_header));
	if (security((t_common*)nm, arch, sizeof(*arch) * header->nfat_arch))
		return ;
	fat_run(arch_lookup(arch, header->nfat_arch, nm->flags), nm);
}
