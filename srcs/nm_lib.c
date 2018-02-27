/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_lib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 13:16:28 by snicolet          #+#    #+#             */
/*   Updated: 2018/02/27 01:08:03 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <ar.h>

static int	load_ar(struct ar_hdr *ar, t_ar *load)
{
	load->ar = ar;
	return (ft_sscanf(ar->ar_name, "%s%u\\s%lu\\s%u\\s%u\\s%x\\s%lu\\s%$",
			AR_EFMT1, &load->len, &load->date, &load->uid, &load->gid,
			&load->mode, &load->size) == 8);
}

static int	lib_cmp(t_ar *a, t_ar *b)
{
	if (a->offset < b->offset)
		return (-1);
	if (a->offset > b->offset)
		return (1);
	return (0);
}

/*
** i store the pl->ar to check if ar->ar_name is equal to '\0'
** in this case it's mean that this offset have already be done
*/

static void	lib_rl_run(t_nm *nm, size_t index, const size_t size, t_ar **tab)
{
	t_ar				*pl;

	while (index < size)
	{
		pl = tab[index++];
		if (!*pl->ar->ar_name)
			continue ;
		nm->subfilename = pl->filename;
		nm->fileraw =
			&nm->rootraw[pl->offset + sizeof(struct ar_hdr) + pl->len];
		nm->magic = *(unsigned int *)(size_t)nm->fileraw;
		nm->filesize = pl->size;
		nm->current_index = (unsigned int)index;
		nm->indexes.sector = 0;
		handle_files_types(nm);
		pl->ar->ar_name[0] = '\0';
	}
}

static void	lib_rl(struct ranlib *rl, size_t index, const size_t size, t_nm *nm)
{
	struct ar_hdr		*ar;
	void				*ptr;
	t_ar				*payload;
	t_ar				**tab;

	if (!(ptr = malloc((sizeof(t_ar) + sizeof(t_ar*)) * size)))
	{
		nm->flags |= NM_ERROR | NM_FLAG_ERROR_MEM;
		return ;
	}
	payload = ptr;
	tab = (t_ar**)((size_t)ptr + (sizeof(t_ar) * size));
	while (index < size)
	{
		ar = (void*)&nm->rootraw[rl->ran_off];
		payload[index].offset = rl->ran_off;
		payload[index].filename = (char*)((size_t)ar + sizeof(*ar));
		load_ar(ar, &payload[index]);
		tab[index] = &payload[index];
		rl++;
		index++;
	}
	ft_quicksort((void**)tab, 0, size - 1, FT_CASTCMP(&lib_cmp));
	lib_rl_run(nm, 0, size, tab);
	free(ptr);
}

void		handle_lib(t_nm *nm)
{
	struct ranlib	*rl;
	struct ar_hdr	*ar;
	char			*symdef;
	int				*size;
	t_ar			ar_read;

	if (ft_memcmp(nm->fileraw, ARMAG, SARMAG))
	{
		nm->flags |= NM_FLAG_ERROR;
		return ;
	}
	nm->flags |= NM_FLAG_LIBRARY | NM_FLAG_SHOWNAME | NM_FLAG_SYMTAB;
	ar = (void*)((size_t)nm->fileraw + SARMAG);
	symdef = (char*)((size_t)&ar[1]);
	ft_printf("library (%s) for %s\n", symdef, nm->filepath);
	load_ar(ar, &ar_read);
	size = (void*)((size_t)nm->fileraw + sizeof(*ar) + SARMAG +
		(size_t)ft_atoi(ar->ar_name + ft_strlen(AR_EFMT1)));
	rl = (void*)((size_t)size + sizeof(int));
	lib_rl(rl, 0, (size_t)*size / sizeof(struct ranlib), nm);
}
