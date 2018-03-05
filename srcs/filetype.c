/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filetype.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 18:26:41 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/05 19:15:08 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"
#include "filetype.h"

/*
** return the proper flags for the file
*/

size_t		filetype(const char *fileraw, const size_t filesize,
	const size_t flags)
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
		{
			if (flags & FLAG_SHOWTYPE)
				ft_printf("%s%s\n", "file type: ", hand->desc);
			return (hand->flags);
		}
	}
	if (filesize >= SARMAG)
	{
		if (!ft_memcmp(fileraw, ARMAG, SARMAG))
			return (FLAG_LIB | FLAG_SNAME | FLAG_SYMTAB);
	}
	return (FLAG_UNKNKOW | FLAG_ERROR);
}
