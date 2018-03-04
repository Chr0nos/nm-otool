/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 16:04:09 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/04 15:32:30 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H
# include "loadfile.h"
# include "libft.h"
# include "swap.h"
# include "flags.h"
# include "common.h"
# include "security.h"
# include <string.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <ar.h>

typedef struct		s_otool
{
	size_t			flags;
	size_t			filesize;
	const char		*filepath;
	unsigned char	*fileraw;
	t_list			*segments;
	char			*rootraw;
	size_t			rfs;
	void			*padding;
}					t_otool;

void				otool_macho_symtab(const size_t ptr, t_list *segments,
		t_common *com);
void				otool_showmem(const unsigned char *ptr,
	const size_t size, const size_t offset, const size_t flags);
void				otool_fat(t_common *com);


#endif
