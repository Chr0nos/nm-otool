/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filetype.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 04:05:51 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/05 14:50:36 by snicolet         ###   ########.fr       */
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

typedef struct				s_filehandler
{
	const char				*desc;
	unsigned int			magic;
	size_t					flags;
	size_t					minsize;
}							t_filehandler;

# pragma pack(pop)

# define HANDLERS_COUNT 7

static const t_filehandler	g_handlers[HANDLERS_COUNT] = {
	(t_filehandler){
		"binary 64bits",
		MH_MAGIC_64,
		FLAG_64BITS | FLAG_MACHO,
		sizeof(unsigned int) + sizeof(struct load_command)
	},
	(t_filehandler){
		"binary 64bits (cigam)",
		MH_CIGAM_64,
		FLAG_64BITS | FLAG_MACHO | FLAG_CIGAM,
		sizeof(unsigned int) + sizeof(struct load_command)
	},
	(t_filehandler){
		"binary 32bits",
		MH_MAGIC,
		FLAG_32BITS | FLAG_MACHO,
		sizeof(unsigned int) + sizeof(struct load_command)
	},
	(t_filehandler){
		"binary 32bits",
		MH_CIGAM,
		FLAG_32BITS | FLAG_MACHO | FLAG_CIGAM,
		sizeof(unsigned int) + sizeof(struct load_command)
	},
	(t_filehandler){
		"fat binary 32 bits",
		FAT_MAGIC,
		FLAG_32BITS | FLAG_FAT,
		sizeof(unsigned int) + sizeof(struct fat_header)
	},
	(t_filehandler){
		"fat binary 32 bits (cigam)",
		FAT_CIGAM,
		FLAG_32BITS | FLAG_FAT | FLAG_CIGAM,
		sizeof(unsigned int) + sizeof(struct fat_header)
	},
	(t_filehandler){
		"fat binary 64 bits (cigam)",
		FAT_MAGIC_64,
		FLAG_64BITS | FLAG_FAT | FLAG_CIGAM,
		sizeof(unsigned int) + sizeof(struct fat_header)
	},
};

size_t						filetype(const char *fileraw,
	const size_t filesize, const size_t flags);

#endif
