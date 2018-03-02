/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_filetype.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 18:26:41 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/02 18:43:49 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

/*
** return the proper flags for the file
*/

size_t		otool_filetype(char *fileraw, const size_t filesize)
{
	unsigned int		magic;

	if ((filesize < 4) || (!fileraw))
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
