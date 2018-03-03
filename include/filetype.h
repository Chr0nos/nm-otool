/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filetype.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 04:05:51 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/03 04:30:46 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILETYPE_H
# define FILETYPE_H
# include "flags.h"
# include <string.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>

# pragma pack(push, 1)

typedef struct		s_filehandler
{
	const char		*desc;
	unsigned int	magic;
	size_t			flags;
	size_t			minsize;
}					t_filehandler;

#pragma pack(pop)

# define TFH t_filehandler
# define HANDLERS_COUNT 6

static const TFH	g_handlers[HANDLERS_COUNT] = {
	(TFH){"binary 64bits", MH_MAGIC_64, FLAG_64BITS | FLAG_MACHO, 4},
	(TFH){"binary 32bits", MH_MAGIC, FLAG_32BITS | FLAG_MACHO, 4},
	(TFH){"cigam 32bits", MH_CIGAM, FLAG_32BITS | FLAG_MACHO | FLAG_CIGAM, 4},
	(TFH){"fat bin 32 bits", FAT_MAGIC, FLAG_32BITS | FLAG_FAT, 4},
	(TFH){"cbin 32 bits", FAT_CIGAM, FLAG_32BITS | FLAG_FAT | FLAG_CIGAM, 4},
	(TFH){"cbin 64 bits", FAT_MAGIC_64, FLAG_64BITS | FLAG_FAT | FLAG_CIGAM, 4},
};

size_t				filetype(const char *fileraw, const size_t filesize);

#endif
