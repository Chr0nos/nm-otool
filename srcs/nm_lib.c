/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_lib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 13:16:28 by snicolet          #+#    #+#             */
/*   Updated: 2018/02/25 07:52:49 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include <ar.h>

static int	load_ar(const struct ar_hdr *ar, t_ar *load)
{
	int				success;

	success = 0;
	ft_memcpy(load->name, ar->ar_name, ft_strsublen(ar->ar_name, ' '));
	success += ft_sscanf(ar->ar_date, "%lu", &load->date);
	success += ft_sscanf(ar->ar_uid, "%u", &load->uid);
	success += ft_sscanf(ar->ar_gid, "%u", &load->gid);
	success += ft_sscanf(ar->ar_mode, "%x", &load->mode);
	success += ft_sscanf(ar->ar_size, "%lu", &load->size);
	ft_printf("%s%s%s%lu%s%u%s%u%s%x%s%lu - final: %d\n",
		"name: ", load->name,
		" date: ", load->date,
		" uid: ", load->uid,
		" gid: ", load->gid,
		" mode: ", load->mode,
		" size: ", load->size, success
	);
	return (success == 5);
}

static void	lib_rl(struct ranlib *rl, const size_t size, t_nm *nm)
{
	size_t				index;
	struct ar_hdr		*ar;
	const char			*name;

	nm->flags |= NM_FLAG_SHOWNAME | NM_FLAG_SYMTAB;
	index = 0;
	while (index < size)
	{
		ar = (void*)&nm->rootraw[rl->ran_off];
		name = (void*)((size_t)ar + sizeof(*ar));
		nm->filepath = name;
		nm->fileraw = (void*)((size_t)name + ft_strlen(name) + 4);
		nm->magic = *(unsigned int *)(size_t)nm->fileraw;
		handle_files_types(nm);
		rl++;
		index += 8;
	}
}

void		handle_lib(t_nm *nm)
{
	struct ranlib	*rl;
	struct ar_hdr	*ar;
	int				*size;
	t_ar			ar_read;

	ft_printf("library for %s\n", nm->filepath);
	if (ft_memcmp(nm->fileraw, ARMAG, SARMAG))
	{
		nm->flags |= NM_FLAG_ERROR;
		return ;
	}
	ar = (void*)((size_t)nm->fileraw + SARMAG);
	load_ar(ar, &ar_read);
	size = (void*)((size_t)nm->fileraw + sizeof(*ar) + SARMAG +
		(size_t)ft_atoi(ar->ar_name + ft_strlen(AR_EFMT1)));
	rl = (void*)((size_t)size + sizeof(int));
	lib_rl(rl, (size_t)*size, nm);
}
