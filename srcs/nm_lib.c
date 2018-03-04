/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_lib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 13:16:28 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/04 17:25:47 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <ar.h>

/*
** i store the pl->ar to check if ar->ar_name is equal to '\0'
** in this case it's mean that this offset have already be done
*/

void		lib_rl_run(t_common *com, size_t index,
	const size_t size, t_ar **tab)
{
	t_nm				*nm;
	t_ar				*pl;
	t_nm				sub;

	nm = (void*)com;
	while (index < size)
	{
		pl = tab[index++];
		if (!*pl->ar->ar_name)
			continue ;
		sub = *nm;
		sub.subfilename = pl->filename;
		sub.fileraw =
			&nm->rootraw[pl->offset + sizeof(struct ar_hdr) + pl->len];
		sub.magic = *(unsigned int *)(size_t)sub.fileraw;
		sub.filesize = pl->size;
		ft_bzero(&sub.indexes, sizeof(nm->indexes));
		handle_files_types(&sub);
		pl->ar->ar_name[0] = '\0';
	}
}
