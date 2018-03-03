/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filetype.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 18:26:41 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/03 04:32:32 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"
#include "filetype.h"

/*
** return the proper flags for the file
*/

// size_t		otool_filetype(char *fileraw, const size_t filesize)
// {
// 	unsigned int		magic;
// 	size_t				minsize;
//
// 	minsize = sizeof(unsigned int) + sizeof(struct mach_header_64) +
// 		sizeof(struct load_command);
// 	if ((filesize < minsize) || (!fileraw))
// 		return (FLAG_UNKNKOW | FLAG_ERROR);
// 	magic = *(unsigned int *)(size_t)fileraw;
// 	if (magic == MH_MAGIC_64)
// 		return (FLAG_64BITS | FLAG_MACHO);
// 	if (magic == MH_CIGAM_64)
// 		return (FLAG_64BITS | FLAG_CIGAM | FLAG_MACHO);
// 	if (magic == MH_MAGIC)
// 		return (FLAG_32BITS | FLAG_MACHO);
// 	if (magic == MH_CIGAM)
// 		return (FLAG_32BITS | FLAG_CIGAM | FLAG_MACHO);
// 	if (magic == FAT_MAGIC_64)
// 		return (FLAG_64BITS | FLAG_FAT);
// 	if (magic == FAT_MAGIC)
// 		return (FLAG_32BITS | FLAG_FAT);
// 	if (filesize >= SARMAG)
// 	{
// 		if (!ft_memcmp(fileraw, ARMAG, SARMAG))
// 			return (FLAG_LIB);
// 	}
// 	return (FLAG_UNKNKOW);
// }

size_t		filetype(const char *fileraw, const size_t filesize)
{
	const t_filehandler		*hand;
	size_t					p;
	unsigned int			magic;

	if (filesize < sizeof(unsigned int))
		return (FLAG_UNKNKOW | FLAG_ERROR);
	magic = *(unsigned int *)(size_t)fileraw;
	p = 0;
	while (p < HANDLERS_COUNT)
	{
		hand = &g_handlers[p++];
		if ((hand->minsize <= filesize) && (hand->magic == magic))
			return (hand->flags);
	}
	if (filesize >= SARMAG)
	{
		if (!ft_memcmp(fileraw, ARMAG, SARMAG))
			return (FLAG_LIB);
	}
	return (FLAG_UNKNKOW);
}
