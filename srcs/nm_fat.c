/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_fat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 02:53:00 by snicolet          #+#    #+#             */
/*   Updated: 2018/02/13 20:32:32 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

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

/*
** this function will iterate throuth all availables architectures from the
** end of the list (to get 64 bits first if available),
** any architecture who's not 32 or 64 bits will return a NM_ERROR,
** thus signal will allow the parent function to continue, the first NM_SUCCESS
** stop the course of the loop
** the filesize will be reduced by the offset,
** the fileraw will be set at the good position,
** please note that the REAL pointer is stored into rootraw and the real size is
** stored into nm->rfs (Real File Size)
** this implementation has been choosen to allow FAT inside FAT etc...
*/

static int	fat_loop(struct fat_arch *arch, t_nm *nm)
{
	if (nm->flags & NM_FLAG_CIGAM)
		fat_fix_cigam(arch);
	if ((arch->cputype == CPU_TYPE_X86_64) || (arch->cputype == CPU_TYPE_X86))
	{
		nm->flags &= NM_FLAG_CIGAM;
		nm->fileraw = &nm->fileraw[arch->offset];
		nm->filesize -= arch->offset;
		nm->magic = *(unsigned int *)(size_t)nm->fileraw;
		handle_files_types(nm);
		return (NM_SUCCESS);
	}
	return (NM_ERROR);
}

void		handle_fat(t_nm *nm)
{
	struct fat_header		*header;
	struct fat_arch			*arch;
	unsigned int			p;

	if (nm_security(nm, header, sizeof(*header)) == NM_ERROR)
		return ;
	(void)show;
	header = (void*)(size_t)nm->fileraw;
	if (nm->flags & NM_FLAG_CIGAM)
		header->nfat_arch = swap(header->nfat_arch);
	arch = (void*)((size_t)nm->fileraw + sizeof(*header));
	if (nm_security(nm, arch, sizeof(*arch)) == NM_ERROR)
		return ;
	p = header->nfat_arch;
	arch += p;
	while ((p--) && (fat_loop(arch--, nm) == NM_ERROR))
		;
}
