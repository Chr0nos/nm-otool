/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_filetype.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 18:26:41 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/02 23:12:35 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

/*
** return the proper flags for the file
*/

size_t		otool_filetype(char *fileraw, const size_t filesize)
{
	unsigned int		magic;
	size_t				minsize;

	minsize = sizeof(unsigned int) + sizeof(struct mach_header_64) +
		sizeof(struct load_command);
	if ((filesize < minsize) || (!fileraw))
		return (FLAG_UNKNKOW | FLAG_ERROR);
	magic = *(unsigned int *)(size_t)fileraw;
	if (magic == MH_MAGIC_64)
		return (FLAG_64BITS | FLAG_MACHO);
	if (magic == MH_CIGAM_64)
		return (FLAG_64BITS | FLAG_CIGAM | FLAG_MACHO);
	if (magic == MH_MAGIC)
		return (FLAG_32BITS | FLAG_MACHO);
	if (magic == MH_CIGAM)
		return (FLAG_32BITS | FLAG_CIGAM | FLAG_MACHO);
	if (filesize >= SARMAG)
	{
		if (!ft_memcmp(fileraw, ARMAG, SARMAG))
			return (FLAG_LIB);
	}
	return (FLAG_UNKNKOW);
}
