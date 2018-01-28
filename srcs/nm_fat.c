/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_fat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 02:53:00 by snicolet          #+#    #+#             */
/*   Updated: 2018/01/28 11:30:06 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static uint32_t	swap(uint32_t x)
{
	return ((x & 0xff000000) >> 24 |
		(x & 0x00ff0000) >> 8 |
		(x & 0x0000ff00) << 8 |
		(x & 0x000000ff) << 24);
}

static void show(struct fat_arch *arch)
{
	ft_printf("%s%9d%s%6d%s%6x%s%6x%s%6x%s%6x\n",
		"cpu type: ", arch->cputype,
		" sub type: ", arch->cpusubtype,
		" offset: ", arch->offset,
		" size: ", arch->size,
		" align: ", arch->align,
		" arch: ", (unsigned int)arch->cputype & CPU_ARCH_MASK);
}

static void	fat_fix_cigam(struct fat_arch *arch)
{
	arch->cputype = (int)(swap((uint32_t)arch->cputype) & 0x7fffffff);
	arch->cpusubtype = (int)(swap((uint32_t)arch->cpusubtype) & 0x7fffffff);
	arch->offset = swap(arch->offset);
	arch->size = swap(arch->size);
	arch->align = swap(arch->align);
}

void		handle_fat(char *fileraw)
{
	struct fat_header		*header;
	struct fat_arch			*arch;
	unsigned int			p;

	header = (void*)(size_t)fileraw;
	if (header->magic == FAT_CIGAM)
		header->nfat_arch = swap(header->nfat_arch);
	arch = (void*)((size_t)fileraw + sizeof(*header));
	p = header->nfat_arch;
	while (p--)
	{
		if (header->magic == FAT_CIGAM)
			fat_fix_cigam(arch);
		if (arch->cputype == CPU_TYPE_X86_64)
		{
			ft_printf("%s", "64 bits found !\n");
			handle_x64(&fileraw[arch->offset]);
			// return ;
		}
		if (arch->cputype == CPU_TYPE_X86)
		{
			ft_printf("%s", "32 bits found.\n");
			handle_x32(&fileraw[arch->offset]);
			// return ;
		}
		show(arch);
		arch++;
	}
}
