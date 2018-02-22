/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_lib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 13:16:28 by snicolet          #+#    #+#             */
/*   Updated: 2018/02/22 13:28:20 by snicolet         ###   ########.fr       */
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

void		handle_lib(t_nm *nm)
{
	struct ar_hdr	*ar;
	t_ar			ar_read;

	ft_printf("library for %s\n", nm->filepath);
	if (ft_memcmp(nm->fileraw, ARMAG, SARMAG))
	{
		nm->flags |= NM_FLAG_ERROR;
		return ;
	}
	ar = (void*)((size_t)nm->fileraw + SARMAG);
	ft_printf("%s%.16s%s%.12s%s%.6s%s%.6s%s%.8s%s%.10s\n",
		"name: ", ar->ar_name,
		" date: ", ar->ar_date,
		" uid: ", ar->ar_uid,
		" gid: ", ar->ar_gid,
		" mode: ", ar->ar_mode,
		" size: ", ar->ar_size);
	load_ar(ar, &ar_read);
	nm->flags |= NM_FLAG_SYMTAB;
}
