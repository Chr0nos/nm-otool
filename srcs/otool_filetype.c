/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_filetype.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 18:26:41 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/02 20:12:33 by snicolet         ###   ########.fr       */
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
		return (OTOOL_FLAG_UNKNKOW | OTOOL_FLAG_ERROR);
	magic = *(unsigned int *)(size_t)fileraw;
	if (magic == MH_MAGIC_64)
		return (OTOOL_FLAG_64BITS);
	if (magic == MH_CIGAM_64)
		return (OTOOL_FLAG_64BITS | OTOOL_FLAG_CIGAM);
	if (magic == MH_MAGIC)
		return (OTOOL_FLAG_32BITS);
	if (magic == MH_CIGAM)
		return (OTOOL_FLAG_32BITS | OTOOL_FLAG_CIGAM);
	if (filesize >= SARMAG)
	{
		if (!ft_memcmp(fileraw, ARMAG, SARMAG))
			return (OTOOL_FLAG_LIB);
	}
	return (OTOOL_FLAG_UNKNKOW);
}
