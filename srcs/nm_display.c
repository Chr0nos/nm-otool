/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 02:16:50 by snicolet          #+#    #+#             */
/*   Updated: 2018/02/09 22:30:43 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static char get_sect_letter(const t_nm *nm, const unsigned int nsect)
{
	if (nsect == nm->indexes.text)
		return ('T');
	if (nsect == nm->indexes.data)
		return ('D');
	if (nsect == nm->indexes.bss)
		return ('B');
	return ('S');
}

char		nm_getletter(const t_sym *sym, const t_nm *nm)
{
	const size_t		type = sym->type & N_TYPE;
	char				ret;

	if (sym->type == N_STAB)
		return ('-');
	ret = '?';
	if (type == N_UNDF)
		ret = (sym->value == 0) ? 'U' : 'C';
	else if (type == N_PBUD)
		ret = 'U';
	else if (type == N_SECT)
		ret = get_sect_letter(nm, sym->nsect);
	else if (type == N_ABS)
		ret = 'A';
	else if (type == N_INDR)
		ret = 'I';
	if ((!(sym->type & N_EXT) && (ret != '?')))
		ret += 32;
	return (ret);
}

void		nm_display_foreach(void *content, void *userdata)
{
	const t_nm		*nm = userdata;
	const t_sym		*sym = content;

	if (sym->type & N_DESC_DISCARDED)
		;
	else if (sym->value > 0)
	{
		ft_printf("%0*lx %c %s\n",
			nm->display_size,
			sym->value, nm_getletter(sym, nm), sym->name);
	}
	else
		ft_printf("%*s %c %s\n", nm->display_size, "", 'U', sym->name);
}
