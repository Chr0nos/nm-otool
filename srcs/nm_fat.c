/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_fat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 02:53:00 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/03 02:19:55 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

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

static void				fat_fix_cigam(struct fat_arch *arch)
{
	arch->cputype = (int)(swap((uint32_t)arch->cputype) & 0x7fffffff);
	arch->cpusubtype = (int)(swap((uint32_t)arch->cpusubtype) & 0x7fffffff);
	arch->offset = swap(arch->offset);
	arch->size = swap(arch->size);
	arch->align = swap(arch->align);
}

static int				fat_run(struct fat_arch *arch, t_nm *nm)
{
	nm->flags &= ~FLAG_CIGAM;
	nm->flags |= FLAG_FAT;
	nm->fileraw = &nm->fileraw[arch->offset];
	nm->filesize -= arch->offset;
	nm->magic = *(unsigned int *)(size_t)nm->fileraw;
	handle_files_types(nm);
	return (NM_SUCCESS);
}

/*
** lookup for the best architecture in a fat binary
** the priority is: X64 > X32 > first found
*/

static struct fat_arch	*arch_lookup(struct fat_arch *arch,
	unsigned int arch_left, const size_t nm_flags)
{
	struct fat_arch		*selected;

	selected = arch;
	while (arch_left--)
	{
		if (nm_flags & FLAG_CIGAM)
			fat_fix_cigam(arch);
		if (arch->cputype == CPU_TYPE_X86)
			selected = arch;
		if (arch->cputype == CPU_TYPE_X86_64)
			return (arch);
		arch++;
	}
	return (selected);
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
