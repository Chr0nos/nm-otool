/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_lib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 13:16:28 by snicolet          #+#    #+#             */
/*   Updated: 2018/03/04 15:29:08 by snicolet         ###   ########.fr       */
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
	t_nm				sub;

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

static void	lib_rl(struct ranlib *rl, size_t index, const size_t size, t_nm *nm)
{
	struct ar_hdr		*ar;
	void				*ptr;
	t_ar				*payload;
	t_ar				**tab;

	if (!(ptr = malloc((sizeof(t_ar) + sizeof(t_ar*)) * size)))
	{
		nm->flags |= NM_ERROR;
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

	ar = (void*)((size_t)nm->fileraw + SARMAG);
	symdef = (char*)((size_t)&ar[1]);
	if (security((t_common*)nm, symdef, 8))
		return ;
	load_ar(ar, &ar_read);
	size = (void*)((size_t)nm->fileraw + sizeof(*ar) + SARMAG +
		(size_t)ft_atoi(ar->ar_name + ft_strlen(AR_EFMT1)));
	rl = (void*)((size_t)size + sizeof(int));
	lib_rl(rl, 0, (size_t)*size / sizeof(struct ranlib), nm);
}
