/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 15:31:45 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/04 15:50:13 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"
#include "arch_lookup.h"
#include "fat.h"
#include "swap.h"

void	fat(t_common *com, void (*callback)(struct fat_arch *, t_common *))
{
	struct fat_header		*header;
	struct fat_arch			*arch;

	header = (void*)(size_t)com->fileraw;
	if (security((t_common*)com, header, sizeof(*header)))
		return ;
	if (com->flags & FLAG_CIGAM)
		header->nfat_arch = swap(header->nfat_arch);
	arch = (void*)((size_t)com->fileraw + sizeof(struct fat_header));
	if (security(com, arch, sizeof(*arch) * header->nfat_arch))
		return ;
	callback(arch_lookup(arch, header->nfat_arch, com->flags), com);
}
