/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_lib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 13:16:28 by snicolet          #+#    #+#             */
/*   Updated: 2018/02/25 16:27:12 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <ar.h>

static int	load_ar(const struct ar_hdr *ar, t_ar *load)
{
	return (ft_sscanf(ar->ar_name, "%s%u\\s%lu\\s%u\\s%u\\s%x\\s%lu\\s%$",
			AR_EFMT1, &load->len, &load->date, &load->uid, &load->gid,
			&load->mode, &load->size) == 8);
}

static void	lib_rl(struct ranlib *rl, const size_t size, t_nm *nm)
{
	size_t				index;
	struct ar_hdr		*ar;
	t_ar				load;

	index = 0;
	while (index < size)
	{
		ar = (void*)&nm->rootraw[rl->ran_off];
		load_ar(ar, &load);
		nm->subfilename = (char*)((size_t)ar + sizeof(*ar));
		nm->fileraw = &nm->rootraw[rl->ran_off + sizeof(*ar) + load.len];
		nm->magic = *(unsigned int *)(size_t)nm->fileraw;
		nm->filesize = load.size;
		nm->current_index = (unsigned int)index + 1;
		handle_files_types(nm);
		rl++;
		index++;
	}
}

void		handle_lib(t_nm *nm)
{
	struct ranlib	*rl;
	struct ar_hdr	*ar;
	char			*symdef;
	int				*size;
	t_ar			ar_read;

	ft_printf("library for %s\n", nm->filepath);
	if (ft_memcmp(nm->fileraw, ARMAG, SARMAG))
	{
		nm->flags |= NM_FLAG_ERROR;
		return ;
	}
	nm->flags |= NM_FLAG_LIBRARY | NM_FLAG_SHOWNAME | NM_FLAG_SYMTAB;
	ar = (void*)((size_t)nm->fileraw + SARMAG);
	symdef = (char*)((size_t)ar + 1);
	load_ar(ar, &ar_read);
	size = (void*)((size_t)nm->fileraw + sizeof(*ar) + SARMAG +
		(size_t)ft_atoi(ar->ar_name + ft_strlen(AR_EFMT1)));
	rl = (void*)((size_t)size + sizeof(int));
	lib_rl(rl, (size_t)*size / sizeof(struct ranlib), nm);
}
