/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_lookup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 15:34:17 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/04 15:38:10 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arch_lookup.h"
#include "flags.h"
#include "swap.h"

static void				fat_fix_cigam(struct fat_arch *arch)
{
	arch->cputype = (int)(swap((uint32_t)arch->cputype) & 0x7fffffff);
	arch->cpusubtype = (int)(swap((uint32_t)arch->cpusubtype) & 0x7fffffff);
	arch->offset = swap(arch->offset);
	arch->size = swap(arch->size);
	arch->align = swap(arch->align);
}

/*
** lookup for the best architecture in a fat binary
** the priority is: X64 > X32 > first found
*/

struct fat_arch	*arch_lookup(struct fat_arch *arch,
	unsigned int arch_left, const size_t flags)
{
	struct fat_arch		*selected;

	selected = arch;
	while (arch_left--)
	{
		if (flags & FLAG_CIGAM)
			fat_fix_cigam(arch);
		if (arch->cputype == CPU_TYPE_X86)
			selected = arch;
		if (arch->cputype == CPU_TYPE_X86_64)
			return (arch);
		arch++;
	}
	return (selected);
}
